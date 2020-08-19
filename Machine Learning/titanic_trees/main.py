import pandas
from sklearn.tree import DecisionTreeClassifier

dataSet = pandas.read_csv('titanic.csv', index_col='PassengerId')
X = dataSet.loc[:, ["Pclass", "Fare", "Age", "Sex"]]
X["Sex"] = X["Sex"].map({"male": 0, "female": 1})
y = dataSet["Survived"]
X = X.dropna()
y = y[X.index]
clf = DecisionTreeClassifier(random_state=241)
clf.fit(X, y)
importances = pandas.Series(clf.feature_importances_, index=X.columns).sort_values(ascending=False)
print(importances)