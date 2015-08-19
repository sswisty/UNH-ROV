% Data processing program that reads in the txt files and parses the values
% into photodiode values
clear;clc;
close all
%% 1) Data Parsing
count=1;
% fileID=fopen(x4.5_y0_z1_upright.txt,r); %1
xi=4.5;
zi=1.2;
yi=0.3;
fileID=fopen(sprintf('x%2g_y%1g_z%1g.txt',xi,yi,zi));
% for xi=4.5:8.5
for zi=1:0.2:1.8
    for yi=-0.6:0.3:0.6
        %fileID=fopen(sprintf('x%2g_y%1g_z%1g.txt',xi,yi,zi));
        N=5;
        data=fread(fileID, [1 inf], '*char');
        
        % Number of detectors on Arduino 1 and 2
        PD1=13;
        PD2=12;
        Psum=PD1+PD2+2; % This property is used for data parsing
        % find 2014 in the file.. Change this to 2015 in the next year
        cycles = strfind(data, '2015');
        fclose(fileID);
        % Day_ind=strfind(data,Day);
        comaind=strfind(data,',');
        % Day_ind=Day_ind(2:end)
        k=2;
        if comaind(14)-comaind(13)<=5
            for i=1:length(cycles)/2
                Ard1(i,:)=str2num(data(cycles(2*i-1)+5 : comaind(Psum*i-PD1)));
                Ard2(i,:)=str2num(data(cycles(2*i)+5: comaind(Psum*i)));
                k=k+1;
            end
        else
            PD1=12;PD2=13;
            for i=1:length(cycles)/2
                Ard2(i,:)=str2num(data(cycles(2*i-1)+5 : comaind(Psum*i-PD1-2)));
                Ard1(i,:)=str2num(data(cycles(2*i)+5: comaind(Psum*i)));
                k=k+1;
            end
            
        end
        PD=[Ard1 Ard2];
        %% Plot of the average
        PDsum=mean(PD);
        stdev(count,:)=std(PD);
        for i=1:5
            B(i,1:5)=PDsum(1,5*i-4:5*i ) ;
        end
        subplot(5,5,count)
        imagesc(B)
        caxis([0 1023])
        %% 2) Moment Calculation
        [row,col]=find(B==max(max(B)));
        row=row(1);
        col=max(col); % Sometimes multiple values are returned. Will pick max
        row;
        %% Sub-pixel accuracy algorithm
        % First derivatives
        dIdx= (B(row,col+1)-B(row,col-1))/2;
        dIdy= (B(row+1,col)-B(row-1,col))/2;
        % Second derivatives
        d2Idx2=B(row,col+1)-2*B(row,col)+B(row,col-1);
        d2Idy2=B(row+1,col)-2*B(row,col)+B(row-1,col);
        % Second partial derivatives
        
        d2Idxdy=0.25*(B(row+1,col+1)+B(row-1,col-1)-B(row-1,col+1)-B(row+1,col-1));
        H=[d2Idx2 d2Idxdy; d2Idxdy d2Idy2];
        D=[dIdx;dIdy];
        S=-inv(H)*D;
        col_sub(count)=col+S(1); % Calculate the sub-pixel accuracy
        row_sub(count)=row+S(2);
        title(sprintf('x=%1gm y=%1gm z=%1gm' ,xi,yi,zi));
        xf=1:N;
        yf=1:N;
        [Ypos,Zpos]=meshgrid(xf,yf);
        Ysort=reshape(Ypos,N*N,1);
        Zsort=reshape(Zpos,N*N,1);
        i=0;li=1;
        for i=0:2
            for j=0:2
                k=1;
                for k=1:N*N
                    Mom(k,li)=((Ysort(k)-col_sub(count))^i) * ((Zsort(k)-row_sub(count))^j)*PDsum(k);
                    Mom_norm(k,li)=Mom(k,li)/sum(PDsum);
                end
                li=li+1;
            end
        end
        Mnt=sum(Mom_norm);
        Mmnt(3*count-2:3*count,:)=transpose(reshape(Mnt,3,3));
        count=count+1;
    end
end

% end
sprintf('row values are between %1g-%1g',min(row_sub),max(row_sub))
sprintf('col values are between %1g-%1g',min(col_sub),max(col_sub))
