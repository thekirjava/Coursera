import pan

dataSet = pandas.read_csv('titanic.csv', index_col='PassengerId')
print(dataSet[dataSet.Sex == "male"].count(), dataSet[dataSet.Sex == "female"].count(), end=" ")
