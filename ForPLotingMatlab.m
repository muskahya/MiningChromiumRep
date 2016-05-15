clear
clc


%  sadece bu iki satiri istediginiz gibi değiştirip farklı developerlar için sonucları inceleyebilirsiniz
fileName = 'topSorted.txt';
lineCount = 16;




file = fopen(fileName);
names = cell(1, lineCount);
numbers = zeros(1, lineCount);


counter = 1;
while lineCount >= counter
    line = fgetl(file);
    name = '';
    number = '';
    [name, number] = strtok(line);
    names{counter} = name;
    numbers(counter) = str2num(number);
    counter = counter + 1;
end

fclose(file);

%names
%numbers

x=1:lineCount;
stem(x, numbers, 'filled', 'MarkerFaceColor', 'blue', 'MarkerEdgeColor', 'blue');
ax = gca;
ax.XTick = x;
ax.XTickLabel = names;
xlabel('Developers');
ylabel('Commit Count');