#include <stdio.h>
#include <string.h>

/* ham loai bo cac ky tu space o dau chuoi */
void bo_space_dau(char *s)
{
    int i = 0, j = 0;
    while (s[i] == ' ') i++; /* bo space */
    while (s[i] != '\0')
    {
        s[j] = s[i];
        j++;
        i++;
    }
    s[j] = '\0';
}

/* ham kiem tra chuoi co hop le la so (co the am) hay khong */
int chuoi_la_so(const char *s)
{
    int i = 0;
    if (s[0] == '\0') return 0;

    /* cho phep dau '-' o dau */
    if (s[0] == '-')
    {
        if (s[1] == '\0') return 0; /* chi co dau '-' thi khong hop le */
        i = 1;
    }

    while (s[i] != '\0')
    {
        if (s[i] < '0' || s[i] > '9')
            return 0;
        i++;
    }
    return 1;
}

/* ham xoa cac so 0 o dau chuoi (tru truong hop chuoi chi co '0') */
void xoa_0_dau(char *s)
{
    int i = 0, j = 0;
    while (s[i] == '0') i++;
    if (s[i] == '\0')
    {
        s[0] = '0';
        s[1] = '\0';
        return;
    }
    while (s[i] != '\0')
    {
        s[j] = s[i];
        j++;
        i++;
    }
    s[j] = '\0';
}

/* ham so sanh hai so lon duong (khong dau am) */
int so_sanh(const char *a, const char *b)
{
    int la = strlen(a);
    int lb = strlen(b);
    if (la > lb) return 1;
    if (la < lb) return -1;
    return strcmp(a, b);
}

/* ham cong hai so duong */
void cong_duong(const char *a, const char *b, char *kq)
{
    char A[1100], B[1100];
    int i, j, nA, nB, n, du, tong, x, y;

    strcpy(A, a);
    strcpy(B, b);
    nA = strlen(A);
    nB = strlen(B);

    for (i = 0; i < nA / 2; i++)
    {
        char t = A[i];
        A[i] = A[nA - 1 - i];
        A[nA - 1 - i] = t;
    }
    for (i = 0; i < nB / 2; i++)
    {
        char t = B[i];
        B[i] = B[nB - 1 - i];
        B[nB - 1 - i] = t;
    }

    n = 0;
    du = 0;
    i = 0;
    while (i < nA || i < nB || du)
    {
        x = (i < nA ? A[i] - '0' : 0);
        y = (i < nB ? B[i] - '0' : 0);
        tong = x + y + du;
        kq[n++] = (char)((tong % 10) + '0');
        du = tong / 10;
        i++;
    }

    kq[n] = '\0';

    for (j = 0; j < n / 2; j++)
    {
        char t = kq[j];
        kq[j] = kq[n - 1 - j];
        kq[n - 1 - j] = t;
    }
}

/* ham tru hai so duong: a >= b */
void tru_duong(const char *a, const char *b, char *kq)
{
    char A[1100], B[1100];
    int nA, nB;
    int i, j, n, muon, x, y, hieu;

    strcpy(A, a);
    strcpy(B, b);
    nA = strlen(A);
    nB = strlen(B);

    for (i = 0; i < nA / 2; i++)
    {
        char t = A[i];
        A[i] = A[nA - 1 - i];
        A[nA - 1 - i] = t;
    }
    for (i = 0; i < nB / 2; i++)
    {
        char t = B[i];
        B[i] = B[nB - 1 - i];
        B[nB - 1 - i] = t;
    }

    muon = 0;
    n = 0;
    i = 0;
    while (i < nA)
    {
        x = A[i] - '0';
        y = (i < nB ? B[i] - '0' : 0);

        x = x - muon;
        if (x < y)
        {
            x += 10;
            muon = 1;
        }
        else
        {
            muon = 0;
        }

        hieu = x - y;
        kq[n++] = (char)(hieu + '0');
        i++;
    }

    while (n > 1 && kq[n - 1] == '0') n--;
    kq[n] = '\0';

    for (j = 0; j < n / 2; j++)
    {
        char t = kq[j];
        kq[j] = kq[n - 1 - j];
        kq[n - 1 - j] = t;
    }
}

/* ham xu ly dau: thuc hien a + b hoac a - b */
void tinh_toan(const char *a, const char *b, char op, char *kq)
{
    char A[1100], B[1100];
    int amA = 0, amB = 0;

    strcpy(A, a);
    strcpy(B, b);

    if (A[0] == '-') { amA = 1; memmove(A, A + 1, strlen(A)); }
    if (B[0] == '-') { amB = 1; memmove(B, B + 1, strlen(B)); }

    xoa_0_dau(A);
    xoa_0_dau(B);

    if (op == '+')
    {
        if (amA == amB)
        {
            cong_duong(A, B, kq);
            if (amA) {
                int l = strlen(kq);
                memmove(kq + 1, kq, l);
                kq[0] = '-';
                kq[l + 1] = '\0';
            }
        }
        else
        {
            int ss = so_sanh(A, B);
            if (ss == 0)
            {
                strcpy(kq, "0");
                return;
            }
            if (ss > 0)
            {
                tru_duong(A, B, kq);
                if (amA) {
                    int l = strlen(kq);
                    memmove(kq + 1, kq, l);
                    kq[0] = '-';
                    kq[l + 1] = '\0';
                }
            }
            else
            {
                tru_duong(B, A, kq);
                if (amB) {
                    int l = strlen(kq);
                    memmove(kq + 1, kq, l);
                    kq[0] = '-';
                    kq[l + 1] = '\0';
                }
            }
        }
    }
    else if (op == '-')
    {
        char Bb[1100];
        strcpy(Bb, b);

        if (Bb[0] == '-') memmove(Bb, Bb + 1, strlen(Bb));
        else
        {
            int l = strlen(Bb);
            memmove(Bb + 1, Bb, l);
            Bb[0] = '-';
            Bb[l + 1] = '\0';
        }

        tinh_toan(a, Bb, '+', kq);
    }
}

int main()
{
    char a[1100], b[1100], kq[1200];
    char op;
    int hop_le;

    printf("Nhap so thu nhat: ");
    fgets(a, sizeof(a), stdin);
    a[strcspn(a, "\n")] = '\0';
    bo_space_dau(a);

    hop_le = chuoi_la_so(a);
    while (!hop_le)
    {
        printf("Khong hop le. Nhap lai so thu nhat: ");
        fgets(a, sizeof(a), stdin);
        a[strcspn(a, "\n")] = '\0';
        bo_space_dau(a);
        hop_le = chuoi_la_so(a);
    }

    printf("Nhap phep toan (+ hoac -): ");
    scanf(" %c", &op);
    while (op != '+' && op != '-')
    {
        printf("Khong hop le. Chi duoc + hoac -. Nhap lai: ");
        scanf(" %c", &op);
    }
    getchar();

    printf("Nhap so thu hai: ");
    fgets(b, sizeof(b), stdin);
    b[strcspn(b, "\n")] = '\0';
    bo_space_dau(b);

    hop_le = chuoi_la_so(b);
    while (!hop_le)
    {
        printf("Khong hop le. Nhap lai so thu hai: ");
        fgets(b, sizeof(b), stdin);
        b[strcspn(b, "\n")] = '\0';
        bo_space_dau(b);
        hop_le = chuoi_la_so(b);
    }

    tinh_toan(a, b, op, kq);

    printf("Ket qua: %s\n", kq);

    return 0;
}

/*
Ghi chu:
- Chi dung so sanh ky tu '0' <= c <= '9'
- Dung chuoi de xu ly so lon, khong dung kieu nguyen
- Xu ly ca so am
- Dung cac ham dung rieng: cong duong, tru duong, so_sanh, xoa_0_dau
*/
