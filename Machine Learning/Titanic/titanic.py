import pandas

dataSet = pandas.read_csv('titanic.csv', index_col='PassengerId')
print(dataSet['Sex'].value_counts())
print(dataSet['Survived'].value_counts(normalize=True))
print(dataSet['Pclass'].value_counts(normalize=True))
print(dataSet['Age'].mean())
print(dataSet['Age'].median())
print(dataSet['SibSp'].corr(dataSet['Parch'], method='pearson'))



