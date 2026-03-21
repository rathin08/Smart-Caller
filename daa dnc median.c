#include<stdio.h>

void merge(int arr[], int left, int mid, int right)
{
    int i = left, j = mid+1, k = 0;
    int temp[right - left  + 1];

    while (i<=mid && j<=right)
    {
        if(arr[i]<arr[j])
            temp[k++] = arr[i++];
        else
            temp[k++] = arr[j++];
    }

    while(i<=mid)
        temp[k++] = arr[i++];

    while(j<=right)
        temp[k++] = arr[j++];

    for(i = left, k = 0; i<=right; i++, k++)
        arr[i] = temp[k];
}

void mergest(int arr[], int left, int right)
{
    if(left < right)
    {
        int mid = (left + right)/2;

        mergest(arr, left, mid);
        mergest(arr, mid+1, right);

        merge(arr, left, mid, right);
    }
}

int main()
{
    int n, i;
    printf("Enter number of elements:\n");
    scanf("%d", &n);

    int arr[n];

    printf("Enter all elements:\n");
    for(i = 0; i<n; i++)
    {
        scanf("%d", &arr[i]);
    }

    mergest(arr, 0, n-1);

    if(n%2==0)
        printf("Median = %.2f\n", (arr[(n/2) - 1] + arr[n/2])/2);
    else
        printf("Median = %d\n", arr[n/2]);

    return 0;
}
