#include <stdio.h>
#include <string.h>

/* kiem tra chuoi chi gom chu so (khong nhan 2.0, khong nhan chu cai) */
int chuoi_chi_so(const char *s)
{
    int i = 0;

    if (s[0] == '\0')
        return 0; // chuoi rong => sai

    while (s[i] != '\0')
    {
        if (s[i] < '0' || s[i] > '9')
            return 0; // gap chu cai hay ky tu => sai
        i++;
    }
    return 1;
}
unsigned long long nhap_so_double(const char *ten)
{
    char buf[256];
    double d;
    unsigned long long kq;

    while (1)
    {
        printf("Nhap %s: ", ten);

        if (fgets(buf, sizeof(buf), stdin) == NULL)
        {
            printf("Loi doc du lieu. Nhap lai.\n");
            clearerr(stdin);
            continue;
        }

        /* xoa newline */
        size_t len = strlen(buf);
        if (len > 0 && buf[len - 1] == '\n')
            buf[len - 1] = '\0';

        /* kiem tra chu so */
        if (!chuoi_chi_so(buf))
        {
            printf("Gia tri khong hop le, chi duoc nhap chu so 0-9. Nhap lai.\n");
            continue;
        }

        /* chuyen sang double */
        if (sscanf(buf, "%lf", &d) != 1)
        {
            printf("Gia tri khong hop le. Nhap lai.\n");
            continue;
        }

        if (d <= 0)
        {
            printf("Phai > 0. Nhap lai.\n");
            continue;
        }

        /* chap nhan tran */
        kq = (unsigned long long)d;
        return kq;
    }
}

void doi_co_so(unsigned long long n, unsigned long long c)
{
    char kq[200];
    int i = 0;
    unsigned long long du;

    if (n == 0)
    {
        printf("Ket qua: 0\n");
        return;
    }

    while (n > 0)
    {
        du = n % c;
        if (du < 10)
            kq[i] = (char)(du + '0');
        else
            kq[i] = (char)(du - 10 + 'A');
        n /= c;
        i++;
    }

    printf("Ket qua: ");
    while (i > 0)
    {
        i--;
        putchar(kq[i]);
    }
    putchar('\n');
}

int main()
{
    unsigned long long n;
    unsigned long long c;

    n = nhap_so_double("n (he thap phan)");
    c = nhap_so_double("co so c (2 - 36)");

    while (c < 2 || c > 36)
    {
        printf("Co so phai tu 2 den 36. Nhap lai.\n");
        c = nhap_so_double("co so c (2 - 36)");
    }

    doi_co_so(n, c);
    return 0;
}

/*
Ghi chu:
- Them kiem tra chu so, neu nhap chu cai => bao loi ngay.
- Khong nhan cac ky tu nhu '-', '+', '.', 'a'...
*/
