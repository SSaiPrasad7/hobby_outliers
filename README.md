# Detection and Replacement of Outliers using Interquartile Range(IQR)
### Outlier
- An observation which differs from an overall pattern on a sample dataset is called an outlier.
### Interquartile Range
- The IQR method divides a data set into quartiles to measure variability.
- The information is arranged in ascending order and divided into four equal parts.(Q1, Q2, Q3, Q4) 
- A dataset has 2*n / 2*n+1 data points, then (n > 2)
    - Q1 : median of the dataset.
    - Q2 : median of n smallest data points.
    - Q3 : median of n highest data points.
- IQR is the range between the first and the third quartiles namely Q1 and Q3 (`IQR = Q3 - Q1`)
- The outliers are data points which fall below `Q1 – 1.5*IQR` or above `Q3 + 1.5*IQR`.
