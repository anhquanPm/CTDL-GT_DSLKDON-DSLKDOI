#include <bits/stdc++.h>
using namespace std;

#define int long long int
#define endl '\n'

struct VatLieu
{
    string maVL;
    string tenVL;
    double donGia;
    int soLuong;
    string dv;
    int thanhTien;
};

VatLieu NhapVatLieu()
{
    VatLieu x;
    cout << "Nhap ma vat lieu: ";
    cin >> x.maVL;
    cin.ignore();
    cout << "Nhap ten vat lieu: ";
    getline(cin, x.tenVL);
    cout << "Nhap so luong: ";
    cin >> x.soLuong;
    cout << "Nhap don gia: ";
    cin >> x.donGia;
    cin.ignore();
    cout << "Nhap don vi: ";
    getline(cin, x.dv);
    x.thanhTien = x.donGia * x.soLuong;
    return x;
}

void XuatVatLieu(VatLieu vl)
{
    cout << setw(10) << vl.maVL
         << setw(30) << vl.tenVL
         << setw(10) << vl.dv
         << setw(10) << vl.soLuong
         << setw(20) << vl.donGia
         << setw(30) << vl.thanhTien
         << "\n";
}

void FORMATVATLIEUBEIN()
{
    cout << "________________________________________________DANH SACH VAT LIEU__________________________________________________\n";
    cout
        << "|STT "
        << setw(10) << "Ma vat lieu"
        << setw(30) << "Ten vat lieu"
        << setw(10) << "Don vi"
        << setw(10) << "So luong"
        << setw(20) << "Don gia"
        << setw(30) << "Thanh tien|"
        << "\n";
}

void FORMATVATLIEUEND()
{
    cout << "|__________________________________________________________________________________________________________________|\n";
}

// DANH SACH LIEN KET DOI
struct NodeVL
{
    VatLieu infor;
    struct NodeVL *next, *prev;
};

struct ListVL
{
    NodeVL *Head;
    NodeVL *Tail;
};

void Init(ListVL &dsvl)
{
    dsvl.Head = NULL;
    dsvl.Tail = NULL;
}

NodeVL *GetNode(VatLieu x)
{
    NodeVL *p;
    p = new NodeVL();
    if (p == NULL)
    {
        cout << "Khong du bo nho\n";
        exit(0);
    }
    p->infor = x;
    p->next = NULL;
    p->prev = NULL;
    return p;
}

void ChenDau(ListVL &dsvl, NodeVL *vl)
{
    if (dsvl.Head == NULL)
    {
        dsvl.Head = vl;
        dsvl.Tail = dsvl.Head;
    }
    else
    {
        vl->next = dsvl.Head;
        dsvl.Head->prev = vl;
        dsvl.Head = vl;
    }
}

void NhapListVL(ListVL &dsvl)
{
    int sl = 1;
    do
    {
        if (sl < 0)
            cout << "So luong phai lon hon 0!\n";
        cout << "Nhap so luong vat lieu can them: \t\t";
        cin >> sl;
    } while (sl <= 0);

    for (int i = 0; i < sl; i++)
    {
        VatLieu x = NhapVatLieu();
        NodeVL *vl = GetNode(x);
        ChenDau(dsvl, vl);
    }
}

void XuatListVL_Dau(ListVL dsvl)
{
    if (dsvl.Head == NULL)
    {
        cout << "\nDanh sach vat lieu rong"<<endl;
        return;
    }
    int dem = 1;
    for (NodeVL *p = dsvl.Head; p != NULL; p = p->next)
    {
        VatLieu v = p->infor;
        cout << setw(3) << dem;
        XuatVatLieu(v);
        dem++;
    }
}

void GhiFileDanhSach(ListVL dsvl, const string &filename)
{
    ofstream outFile(filename, ios::out);
    if (!outFile)
    {
        cerr << "Khong the mo file " << filename << " de ghi!" << endl;
        return;
    }

    // Write the number of elements in the list
    int numElements = 0;
    for (NodeVL *p = dsvl.Head; p != nullptr; p = p->next)
    {
        numElements++;
    }
    outFile << numElements << endl;

    // Write each element to the file
    for (NodeVL *p = dsvl.Head; p != nullptr; p = p->next)
    {
        outFile << p->infor.maVL << "\n";
        outFile << p->infor.tenVL << "\n";
        outFile << p->infor.soLuong << "\n";
        outFile << p->infor.donGia << "\n";
        outFile << p->infor.dv << "\n";
        outFile << p->infor.thanhTien << "\n";
    }

    outFile.close();
}

void DocFileDanhSach(ListVL &dsvl, const string &filename)
{
    ifstream inFile(filename, ios::in);
    if (!inFile)
    {
        cerr << "Khong the mo file " << filename << " de doc!" << endl;
        return;
    }

    int numElements;
    inFile >> numElements;
    inFile.ignore(); // Consume the newline character

    for (int i = 0; i < numElements; i++)
    {
        VatLieu x;
        getline(inFile, x.maVL);
        getline(inFile, x.tenVL);
        inFile >> x.soLuong;
        inFile >> x.donGia;
        inFile.ignore(); // Consume the newline character
        getline(inFile, x.dv);
        inFile >> x.thanhTien;
        inFile.ignore(); // Consume the newline character

        NodeVL *vl = GetNode(x);
        ChenDau(dsvl, vl);
    }

    inFile.close();
}

// so luong vat lieu co trong danh sach
int SoLuongVLTrongDS(ListVL dsvl)
{
    int sl = 0;
    NodeVL *p;
    for (p = dsvl.Head; p != NULL; p = p->next)
    {
        sl++;
    }
    return sl;
}

// Tinh tong tien cac vat lieu co trong danh sach vat lieu
int Tong_Tien_DS_VL(ListVL dsvl)
{
    double sum = 0;
    NodeVL *p;
    for (p = dsvl.Head; p != NULL; p = p->next)
    {
        sum += p->infor.thanhTien;
    }
    return sum;
}

// Vat lieu co so luong lon nhat trong kho
void vatLieuCoSoLuongTrongKhoLonNhatLa(ListVL l)
{
    NodeVL *p;
    map<string, int> myMap;

    if (l.Head == NULL)
    {
        cout << "\n Danh sach rong";
        return;
    }

    for (p = l.Head; p != NULL; p = p->next)
    {
        string tenVl = p->infor.tenVL;
        int soLuong = p->infor.soLuong;

        myMap[tenVl] += soLuong;
    }

    cout << "\n\t\t\t ---VAT-LIEU-CO-SO-LUONG-NHIEU-NHAT-TRONG-KHO-LA---\n";
    auto maxElement = max_element(myMap.begin(), myMap.end(),
                                  [](const auto &p1, const auto &p2)
                                  {
                                      return p1.second < p2.second;
                                  });

    cout << "\t\t\tTen vat lieu: " << maxElement->first << " --- So luong trong kho " << maxElement->second << endl;
}

// Vat lieu co so luong it nhat trong kho
void vatLieuCoSoLuongItNhatTrongKho(ListVL l)
{
    NodeVL *p;
    map<string, int> myMap;

    if (l.Head == NULL)
    {
        cout << "\n Danh sach rong";
        return;
    }

    for (p = l.Head; p != NULL; p = p->next)
    {
        string tenVl = p->infor.tenVL;
        int soLuong = p->infor.soLuong;

        myMap[tenVl] += soLuong;
    }

    cout << "\n\t\t\t ---VAT-LIEU-CO-SO-LUONG-NHIEU-NHAT-TRONG-KHO-LA---\n";
    auto minElement = min_element(myMap.begin(), myMap.end(),
                                  [](const auto &p1, const auto &p2)
                                  {
                                      return p1.second < p2.second;
                                  });

    cout << "\t\t\tTen vat lieu: " << minElement->first << " --- So luong trong kho " << minElement->second << endl;
}

// sua vat lieu theo ma vat lieu
void SuaVatLieu(ListVL &dsvl, const string &maVL)
{
    NodeVL *p;
    for (p = dsvl.Head; p != NULL; p = p->next)
    {
        if (p->infor.maVL == maVL)
        {
            cin.ignore();
            cout << "Nhap ten vat lieu moi: ";
            getline(cin, p->infor.tenVL);
            cout << "Nhap so luong moi: ";
            cin >> p->infor.soLuong;
            cout << "Nhap don gia moi: ";
            cin >> p->infor.donGia;
            cin.ignore();
            cout << "Nhap don vi moi: ";
            getline(cin, p->infor.dv);
            p->infor.thanhTien = p->infor.donGia * p->infor.soLuong;
            cout << "Vat lieu da duoc cap nhat.\n";
            return;
        }
    }
    cout << "Khong tim thay vat lieu voi ma " << maVL << ".\n";
}

// sap xep danh sach vat lieu xay dung tang dan theo so luong trong kho
void sapXepDanhSachVatLieuXayDungTangDanTheoSoLuongHangTrongKho(ListVL &l)
{
    VatLieu tg;
    NodeVL *p, *q;
    if (l.Head == NULL)
    {
        cout << "\n Danh sach rong";
        return;
    }
    for (p = l.Head; p != NULL; p = p->next)
    {
        for (q = p->next; q != NULL; q = q->next)
        {
            if (p->infor.soLuong > q->infor.soLuong)
            {
                tg = p->infor;
                p->infor = q->infor;
                q->infor = tg;
            }
        }
    }
}

void sapXepDanhSachVatLieuXayDungGiamDanTheoThanhTien(ListVL &l)
{
    VatLieu tg;
    NodeVL *p, *q;
    if (l.Head == NULL)
    {
        cout << "\n Danh sach rong";
        return;
    }
    for (p = l.Head; p != NULL; p = p->next)
    {
        for (q = p->next; q != NULL; q = q->next)
        {
            if (p->infor.thanhTien < q->infor.thanhTien)
            {
                tg = p->infor;
                p->infor = q->infor;
                q->infor = tg;
            }
        }
    }
}

void menuKho()
{
    ListVL l;
    Init(l);
    int luachon;
    string maVLToEdit;
    while (true)
    {
        system("cls");
        cout << "\n\t\t\t --------------------------------------MENU-KHO----------------------------------------";
        cout << "\n\t\t\t 1. Nhap danh sach vat lieu trong kho";
        cout << "\n\t\t\t 2. Xuat danh sach vat lieu trong kho";
        cout << "\n\t\t\t 3. So luong vat lieu trong danh sach vat lieu";
        cout << "\n\t\t\t 4. Vat lieu co so luong trong kho lon nhat";
        cout << "\n\t\t\t 5. Vat lieu co so luong trong kho be nhat";
        cout << "\n\t\t\t 6. Sua vat lieu dua vao ma vat lieu";
        cout << "\n\t\t\t 7. Sap xep danh sach vat lieu tang dan theo so luong dang co trong kho cua vat lieu";
        cout << "\n\t\t\t 8. Sap xep giam dan danh sach vat lieu giam dan theo don gia";
        cout << "\n\t\t\t 9. Ghi file";
        cout << "\n\t\t\t 10.Doc file";
        cout << "\n\t\t\t 0. Quay lai";
        cout << "\n\t\t\t --------------------------------------------------------------------------------------";
        cout << "\n\t\t\t Nhap lua chon: ";

        cin >> luachon;
        system("cls");
        switch (luachon)
        {

        case 0:
            return;
            break;

        case 1:
            int sl;
            do
            {
                cout << "test:";
                cin >> sl;
            } while (sl > 0 && sl < 10);
            NhapListVL(l);
            GhiFileDanhSach(l, "vatlieu.dat");
            cout << "Danh sach vat lieu da duoc ghi vao file 'vatlieu.dat'." << endl;
            system("pause");
            system("cls");
            break;

        case 2:
            Init(l);
            DocFileDanhSach(l, "vatlieu.dat");
            cout << "Danh sach vat lieu da duoc doc tu file 'vatlieu.dat':" << endl;
            FORMATVATLIEUBEIN();
            XuatListVL_Dau(l);
            FORMATVATLIEUEND();
            system("pause");
            system("cls");
            break;

        case 3:
            cout << "\n So luong vat lieu trong danh sach vat lieu la: " << SoLuongVLTrongDS(l) << endl;
            system("pause");
            system("cls");
            break;

        case 4:
            vatLieuCoSoLuongTrongKhoLonNhatLa(l);
            system("pause");
            system("cls");
            break;

        case 5:
            vatLieuCoSoLuongItNhatTrongKho(l);
            system("pause");
            system("cls");
            break;

        case 6:
        {
            cout << "Nhap ma vat lieu can sua: ";
            cin >> maVLToEdit;
            SuaVatLieu(l, maVLToEdit);
            system("pause");
            system("cls");
            break;
        }

        case 7:
            cout << "\n\t\t--DANH SACH VAT LIEU XAY DUNG SAP XEP TANG DAN THEO SO LUONG HANG TRONG KHO--" << endl;
            sapXepDanhSachVatLieuXayDungTangDanTheoSoLuongHangTrongKho(l);
            FORMATVATLIEUBEIN();
            XuatListVL_Dau(l);
            FORMATVATLIEUEND();
            system("pause");
            system("cls");
            break;

        case 8:
            cout << "\n\t\t--DANH SACH VAT LIEU XAY DUNG SAP XEP GIAM DAN THEO THANH TIEN--" << endl;
            sapXepDanhSachVatLieuXayDungGiamDanTheoThanhTien(l);
            FORMATVATLIEUBEIN();
            XuatListVL_Dau(l);
            FORMATVATLIEUEND();
            system("pause");
            system("cls");
            break;

        case 9:
            GhiFileDanhSach(l, "vatlieu.dat");
            cout << "Danh sach vat lieu da duoc ghi vao file 'vatlieu.dat'." << endl;
            system("pause");
            system("cls");
            break;

        case 10:
            Init(l);
            DocFileDanhSach(l, "vatlieu.dat");
            cout << "Danh sach vat lieu da duoc doc tu file 'vatlieu.dat':" << endl;
            FORMATVATLIEUBEIN();
            XuatListVL_Dau(l);
            FORMATVATLIEUEND();
            system("pause");
            system("cls");
            break;

        default:
            cout << "\n\t\t\tLua chon khong phu hop" << endl;
            system("pause");
            break;
        }
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------


// Them vat lieu khi vao trong hoa don
void Them_VL_Vao_HD(ListVL listVLFile, ListVL &listVLHD, int stt)
{
    int pnt = 1;
    int slvl;
    NodeVL *p;
    for (p = listVLFile.Head; p != NULL; p = p->next)
    {
        if (pnt == stt)
        {
            int tmp = 0;
            cout << p->infor.tenVL << endl;
            do
            {
                cout << "Nhap so luong vat lieu: ";
                cin >> slvl;
                if (p->infor.soLuong == 0 || p->infor.soLuong < slvl)
                {
                    cout << "\nVat lieu [" << p->infor.tenVL << "] trong kho da het hoac khong du, quy khach vui long chon vat lieu khac" << endl;
                    return;
                }

            } while (slvl < 0 || slvl > p->infor.soLuong || slvl == 0);
            p->infor.soLuong -= slvl;
            VatLieu x;
            x.tenVL = p->infor.tenVL;
            x.donGia = p->infor.donGia;
            x.soLuong = slvl;
            x.thanhTien = slvl * x.donGia;
            x.maVL = p->infor.maVL;
            x.dv = p->infor.dv;
            NodeVL *VL = GetNode(x);
            ChenDau(listVLHD, VL);
            cout << "Them vat lieu vao trong hoa don thanh cong\n";
            GhiFileDanhSach(listVLFile, "vatlieu.dat");
        }
        pnt++;
    }
}

void MenuListVl(ListVL &dsvl)
{
    int choose;
    ListVL dsvlFile;
    Init(dsvlFile);
    DocFileDanhSach(dsvlFile, "vatlieu.dat");
    do
    {
        FORMATVATLIEUBEIN();
        XuatListVL_Dau(dsvlFile);
        cout << "0.  Dung chon vat lieu\n";
        FORMATVATLIEUEND();
        cout << "Moi ban chon stt vat lieu trong kho de dien vao khoa don:";
        cin >> choose;
        if (choose > 0 && choose <= SoLuongVLTrongDS(dsvlFile))
        {
            NodeVL *p;
            VatLieu temp;
            int dem = 1;
            for (p = dsvlFile.Head; p != NULL; p = p->next)
            {
                if (dem == choose)
                {
                    Them_VL_Vao_HD(dsvlFile, dsvl, dem);
                }
                dem++;
            }
        }

        if (choose > SoLuongVLTrongDS(dsvlFile) || choose < 0)
            {
                cout << "\nSTT ban chon khong ton tai trong danh sach vat lieu" << endl;
                cout << "\nDUNG NHAP HOA DON, DO BAN NHAP SAI STT VAT LIEU TRONG DS VAT LIEU"<<endl;
            }

    } while (choose > 0 && choose <= SoLuongVLTrongDS(dsvlFile));
}

// ----------------------------------------------HOADON--------------------------------------------------------------------------
struct HoaDon
{
    string maHoaDon;
    string ngayLap;
    string khachHang;
    string makhachhang;
    int soLoaiVatLieu;
    int tongTien = 0;
    string sdt;
    int thueVAT;
    int tongTienThanhToan;
    ListVL dsvl;
};
struct NodeHD
{
    HoaDon info;
    NodeHD *next;
};

struct ListHD
{
    NodeHD *Head;
    NodeHD *Tail;
};

void InitHD(ListHD &listhd)
{
    listhd.Head = NULL;
    listhd.Tail = NULL;
}

bool isEmty(ListHD list)
{
    if (list.Head == NULL)
        return true;
    return false;
}

NodeHD *taoNodeHD(HoaDon hd)
{
    NodeHD *p = new NodeHD;
    if (p == NULL)
    {
        cout << "Khong du bo nho!\n";
        return NULL;
    }
    p->info = hd;
    p->next = NULL;
    return p;
}

void addHeadHD(ListHD &list, HoaDon hd)
{
    NodeHD *node = taoNodeHD(hd);
    if (node == NULL)
        exit(0);
    if (!isEmty(list))
    {
        node->next = list.Head;
        list.Head = node;
    }
    else
    {
        list.Head = node;
        list.Tail = node;
    }
}

void addTailHD(ListHD &list, HoaDon hd)
{
    NodeHD *node = taoNodeHD(hd);
    if (node == NULL)
        exit(0);
    if (!isEmty(list))
    {
        list.Tail->next = node;
        list.Tail = node;
    }
    else
    {
        list.Head = node;
        list.Tail = node;
    }
}

HoaDon NhapHoaDon(ListHD listhd)
{
    HoaDon hd;
    fflush(stdin);

    bool flag = false;
    do
    {
        if (flag == true)
        {
            cout << "\nMa hoa don da ton tai!";
        }
        cout << "\nMa hoa don: \t";
        cin >> hd.maHoaDon;
        flag = false;
        for (NodeHD *p = listhd.Head; p != NULL; p = p->next)
        {
            if ((p->info).maHoaDon == hd.maHoaDon)
            {
                flag = true;
                break;
            }
        }
    } while (flag);
    fflush(stdin);
    cout << "Ngay lap: \t";
    getline(cin, hd.ngayLap);
    fflush(stdin);
    cout << "Khach hang: \t";
    getline(cin, hd.khachHang);
    cout << "Ma khach hang: \t";
    getline(cin, hd.makhachhang);
    cout << "So dien thoai: \t";
    getline(cin, hd.sdt);
    Init(hd.dsvl);
    MenuListVl(hd.dsvl);

    hd.soLoaiVatLieu = SoLuongVLTrongDS(hd.dsvl);
    cout << endl
         << "So luong vat lieu trong hoa don: " << hd.soLoaiVatLieu << endl;
    hd.tongTien = Tong_Tien_DS_VL(hd.dsvl);
    cout << "Nhap thue vat:";
    cin >> hd.thueVAT;
    hd.tongTienThanhToan = hd.tongTien - hd.thueVAT;
    return hd;
}

void XoaHoaDonVoiDanhSachRong(ListHD &listhd) {
    NodeHD *current = listhd.Head;
    NodeHD *prev = NULL;

    while (current != NULL) {
        // Check if the materials list is empty
        if (current->info.dsvl.Head == NULL) {
            if (prev == NULL) {
                // First node in the list
                listhd.Head = current->next;
                delete current;
                current = listhd.Head;
            } else {
                // Middle or last node in the list
                prev->next = current->next;
                if (current == listhd.Tail) {
                    listhd.Tail = prev;
                }
                delete current;
                current = prev->next;
            }
        } else {
            // Move to next node if materials list is not empty
            prev = current;
            current = current->next;
        }
    }
}

void XuatHoaDon(HoaDon hd)
{
    cout << "\n\n";
    cout << "______________________________________________HOA_DON______________________________________________\n";
    cout << "Ma hoa don:\t\t" << hd.maHoaDon << endl;
    cout << "Ngay lap:\t\t" << hd.ngayLap << endl;
    cout << "Khach hang:\t\t" << hd.khachHang << endl;
    cout << "Ma khach hang:\t\t" << hd.makhachhang << endl;
    cout << "SDT:" << hd.sdt << endl;
    FORMATVATLIEUBEIN();
    XuatListVL_Dau(hd.dsvl);
    FORMATVATLIEUEND();
    cout << "Tong tien:\t\t" << hd.tongTien << endl;
}

void nhapListHD(ListHD &list)
{
    int sl = 1;
    do
    {
        if (sl < 0)
            cout << "So luong phai lon hon 0!\n";
        cout << "Nhap so luong hoa don can them: \n";
        cin >> sl;
    } while (sl < 0);

    for (int i = 0; i < sl; i++)
    {
        cout << "\n\n\n\tHoa don thu " << i + 1;
        addTailHD(list, NhapHoaDon(list));
    }
}
void inDSHoaDon(ListHD listhd)
{
    for (NodeHD *p = listhd.Head; p != NULL; p = p->next)
    {
        XuatHoaDon(p->info);
    }
}
void inListHoaDon(const ListHD list)
{
    NodeHD *node = list.Head;
    while (node != NULL)
    {
        XuatHoaDon(node->info);
        node = node->next;
    }
}
int soLuongHoaDonByDS(const ListHD list)
{
    int dem = 0;
    for (NodeHD *p = list.Head; p != NULL; p = p->next)
    {
        dem++;
    }
    return dem;
}
void ghiFileHD(const ListHD list)
{
    ofstream file("hoadon.dat", ios::binary);
    if (!file.is_open())
    {
        cout << "Không thể mở file!" << endl;
        return;
    }
    file << soLuongHoaDonByDS(list) << endl;
    NodeHD *node = list.Head;
    while (node != NULL)
    {
        HoaDon h = node->info;
        file << h.maHoaDon << endl;
        file << h.ngayLap << endl;
        file << h.khachHang << endl;
        file << h.makhachhang << endl;
        file << h.soLoaiVatLieu << endl;
        file << h.tongTien << endl;
        file << h.sdt << endl;
        file << h.thueVAT << endl;
        file << h.tongTienThanhToan << endl;
        for (NodeVL *p = h.dsvl.Head; p != NULL; p = p->next)
        {
            VatLieu v = p->infor;
            file << v.maVL << endl;
            file << v.tenVL << endl;
            file << v.soLuong << endl;
            file << v.donGia << endl;
            file << v.dv << endl;
            file << v.thanhTien << endl;
        }
        node = node->next;
    }
    file << endl;
    file.close();
}

void docFileHoaDon(ListHD &list)
{
    ifstream file("hoadon.dat", ios::binary);
    if (!file.is_open())
    {
        cout << "Không thể mở file!" << endl;
        return;
    }

    int sl = 0;
    file >> sl;
    file.ignore();
    for (int i = 0; i < sl; i++)
    {
        HoaDon hd;
        getline(file, hd.maHoaDon);
        getline(file, hd.ngayLap);
        getline(file, hd.khachHang);
        getline(file, hd.makhachhang);
        file >> hd.soLoaiVatLieu;
        file >> hd.tongTien;
        file >> hd.sdt;
        file >> hd.thueVAT;
        file >> hd.tongTienThanhToan;
        file.ignore();
        Init(hd.dsvl);
        for (int i = 0; i < hd.soLoaiVatLieu; i++)
        {
            VatLieu vl;
            getline(file, vl.maVL);
            getline(file, vl.tenVL);
            file >> vl.soLuong;
            file >> vl.donGia;
            file.ignore();
            getline(file, vl.dv);
            file >> vl.thanhTien;
            file.ignore();
            ChenDau(hd.dsvl, GetNode(vl));
        }
        addTailHD(list, hd);
    }

    file.close();
}

bool xoaHoaDonTheoMa(ListHD &listhd, string mhd)
{
    if ((listhd.Head->info).maHoaDon == mhd)
    {
        NodeHD *temp = listhd.Head->next;
        delete listhd.Head;
        listhd.Head = temp;
        return true;
    }
    for (NodeHD *p = listhd.Head; p != NULL; p = p->next)
    {
        if (((p->next)->info).maHoaDon == mhd)
        {
            NodeHD *temp = ((p->next)->next);
            delete p->next;
            p->next = temp;
            return true;
        }
    }
    return false;
}

void timHDTheoMa(const ListHD list)
{
    fflush(stdin);
    string mhd;
    cout << "Nhap ma hoa don can tim: ";
    getline(cin, mhd);
    for (NodeHD *p = list.Head; p != NULL; p = p->next)
    {
        if ((p->info).maHoaDon == mhd)
        {
            XuatHoaDon(p->info);
            break;
        }
    }
}

void timHDTheoTenKh(const ListHD list)
{
    string tenkh;
    cout << "Nhap ten khach hang can tim: ";
    getline(cin, tenkh);
    for (NodeHD *p = list.Head; p != NULL; p = p->next)
    {
        if ((p->info).khachHang == tenkh)
        {
            XuatHoaDon(p->info);
        }
    }
}

bool sortHDByTongTien(ListHD &list)
{
    if (isEmty(list))
    {
        cout << "\nDanh sach vat lieu trong!\n";
        return false;
    }
    for (NodeHD *p = list.Head; p != NULL; p = p->next)
    {
        for (NodeHD *q = p->next; q != NULL; q = q->next)
        {
            if ((q->info).tongTienThanhToan > (p->info).tongTienThanhToan)
            {
                HoaDon temp;
                temp = (p->info);
                p->info = q->info;
                q->info = temp;
            }
        }
    }
    return true;
}

void menuHoaDon(ListHD &listhd)
{
    int select;
    while (true)
    {
        system("cls");
        cout << "\n\t\t\t ----------------MENU-HOA-DON------------------";
        cout << "\n\t\t\t 1. Nhap danh sach Hoa Don";
        cout << "\n\t\t\t 2. Xuat danh sach Hoa Don";
        cout << "\n\t\t\t 3. Xoa hoa don theo ma";
        cout << "\n\t\t\t 4. Tim kiem hoa don theo ma";
        cout << "\n\t\t\t 5. Tim kiem hoa don theo ten khach hang";
        cout << "\n\t\t\t 6. Sap xep hoa don theo tong tien tang dan";
        cout << "\n\t\t\t 0. QUAY LAI";
        cout << "\n\t\t\t ----------------------------------------------";
        cout << "\n\t\t\t Nhap lua chon cua ban: ";

        cin >> select;
        string mhd;
        system("cls");
        switch (select)
        {
        case 0:
            return;
            break;
        case 1:
            nhapListHD(listhd);
            XoaHoaDonVoiDanhSachRong(listhd);
            ghiFileHD(listhd);
            system("pause");
            system("cls");
            break;
        case 2:
            cout << "\n\t\tDanh sach hoa don:";
            inDSHoaDon(listhd);
            system("pause");
            system("cls");
            break;
        case 3:
            cout << "\nNhap ma hoa don can xoa: ";
            getline(cin, mhd);
            if (xoaHoaDonTheoMa(listhd, mhd))
            {
                cout << "\nXoa thanh cong hoa don co ma la " << mhd;
            }
            else
            {
                cout << "Khong tim thay ma hoa don can xoa!";
            }
            ghiFileHD(listhd);
            system("pause");
            system("cls");
            break;
        case 4:
            timHDTheoMa(listhd);
            system("pause");
            system("cls");
            break;
        case 5:
            timHDTheoTenKh(listhd);
            system("pause");
            system("cls");
            break;
        case 6:
            if (sortHDByTongTien(listhd))
            {
                cout << "\nSap xep thanh cong!";
            }
            else
            {
                cout << "\nSap xep that bat";
            }
            ghiFileHD(listhd);
            system("pause");
            system("cls");
            break;
        default:
            cout << "\nLua chon khong hop le" << endl;
            system("pause");
            break;
        }
    }
}

// MENU CHÍNH----------------------------------------------------------------------------------------------------------
void mainMenu(ListHD &listhd)
{
    int luachon;
    while (true)
    {
        system("cls");
        cout << "\n\t\t\t ----------------MENU------------------";
        cout << "\n\t\t\t 1. KHO";
        cout << "\n\t\t\t 2. HOA DON";
        cout << "\n\t\t\t 3. DANH DACH THANH VIEN NHOM";
        cout << "\n\t\t\t 0. THOAT";
        cout << "\n\t\t\t --------------------------------------";
        cout << "\n\t\t\t Nhap lua chon cua ban: ";

        cin >> luachon;
        switch (luachon)
        {

        case 0:
            exit(1);
            break;

        case 1:
            menuKho();
            system("pause");
            system("cls");
            break;

        case 2:
            menuHoaDon(listhd);
            system("pause");
            system("cls");
            break;

        case 3:
            cout << "\n\t\t\t -------------------- ";
            cout << "\n\t\t\t | Nguyễn Văn Phúc  |";
            cout << "\n\t\t\t | Trần Anh Quân    |";
            cout << "\n\t\t\t | Nguyễn Thế Thành |";
            cout << "\n\t\t\t -------------------- " << endl;
            system("pause");
            system("cls");
            break;
        default:
            cout << "\n\t\t\tLua chon cua ban khong phu hop" << endl;
            system("pause");
            break;
        }
    }
}

main()
{
    ListHD listhd;
    InitHD(listhd);
    docFileHoaDon(listhd);

    mainMenu(listhd);
    system("pause");

    return 0;
}
