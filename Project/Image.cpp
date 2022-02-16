#include "Image.h"

Image::Image():m_width(0), m_height(0), m_channals(0){}
Image::~Image(){}

int Image::getImageInfo(Mat &src)
{
	if (!src.data)
	{
		std::cout << "empty\n";
        return -1;
	}

	m_height = src.rows;
	m_width = src.cols;
	m_channals = src.channels();
	m_ori = src.clone();
	return 0;
}

int Image::getInfo(int x, int y, int channels)	//��ǥ ȭ�� ���� �޾ƿ���
{ 
	return m_ori.at<Vec3b>(Point(x, y))[channels];
}

int Image::biLinear(float x, float y,int channels)	//�缱�� ������
{ 
	int ix[4], iy[4];                 //���� ������ ȭ��
	int shang, xia, zhi;
	float dx, dy;                 
	if (x >= m_width || y>=m_height || x<0 || y<0) //���� ���� ���� ���
		return 0;                    //0 ��ȯ

	ix[0] = x;                         // ������ f(i , j)
	iy[0] = y;

	dx = x - ix[0];                      
	dy = y - iy[0];
	ix[1] = ix[0] + 1; iy[1] = iy[0];      // �������� �������� ���� ������ ��ǥ
	ix[2] = ix[0];   iy[2] = iy[0] + 1;
	ix[3] = ix[0] + 1; iy[3] = iy[0] + 1;
	for (int l = 1; l <= 4; l++)
	{
		if (ix[l-1] >= m_width)
			ix[l-1] = ix[l-1] - 1;
		if (iy[l-1] >= m_height)
			iy[l-1] = iy[l-1] - 1;
	}
	shang = getInfo(ix[0], iy[0],channels)*(1 - dx) + getInfo(ix[1], iy[1],channels)*dx;
	xia = getInfo(ix[2], iy[2], channels)*(1 - dx) + getInfo(ix[3], iy[3], channels)*dx;
	zhi = shang*(1 - dy) + xia*dy;//���ο� ��ǥ ȭ�� ��
	return zhi;
}

double Image::BSpline(int s, double t)	//B-Spline
{ 
	double Gt = 0;
	if (s == 0)
		Gt = (-pow(t,3.0) + 3 * t * t - 3 * t + 1) / 6;
	else if (s == 1)
		Gt = (3 * pow(t,3.0) - 6 * t * t + 4) / 6;
	else if (s == 2)
		Gt = (-3 * pow(t,3.0) + 3 * t * t + 3 * t + 1) / 6;
	else if (s == 3)
		Gt = pow(t,3.0) / 6;
	return Gt;
}

int Image::waterWaveTrans(Mat &src, Mat &dst)	//�� �ĵ�
{ 
	dst = src.clone();
	float a, b;
	float shui=0;
	cout<<"shuiwenbo input(1 ~ 10):"<<endl;
	cin>>shui;
	for (int y = 0; y < m_height; y++)
	{
	   for (int x = 0; x < m_width; x++)
	   {
			int x2 = x - 0.5*m_width;                 //�߽����� ������ �Ÿ�
			int y2 = y - 0.5*m_height;

			float r = sqrt((float)(x2*x2 + y2*y2));       //����ǥ�� ǥ��
			float th = atan2((float)y2, (float)x2);

			float r2 = 0.5*m_width;                  //�ִ� ȸ�� ������
			if (r>r2) 
			{                                //�ִ� ȸ�� �������� �ʰ��� ���
				for (int k = 0; k < m_channals; k++)
					dst.at<Vec3b>(Point(x, y))[k] = biLinear(x, y, k);
				continue;                                 //��ǥ �״�� ����
			}
		
			a = r * cos(th + sin(shui / 20.0 * r + 0.10)) + r2;              //�ʰ����� ���� ��� �� �ĵ� ����
			b = r * sin(th + sin(shui / 20.0 * r + 0.10)) + r2;

			for (int k = 0; k < m_channals; k++)
			{
				if ((uchar)biLinear(a, b, k))
					dst.at<Vec3b>(y, x)[k] = (uchar)biLinear(a, b, k);
			}
		}
	}
	return 0;
}

int Image::rotateWaveTrans(Mat &src, Mat &dst){ //�̹��� ȸ�� ����
	dst = src.clone();
	float a, b;
	float th=0;
	cout<<"luzhuan input(1 ~ 10):"<<endl;
	cin>>th;
	for (int y = 0; y < m_height; y++)
	{
		for (int x = 0; x < m_width; x++)
		{
			int x2 = x - 0.5*m_width;                 //�߽����� ������ �Ÿ�
			int y2 = y - 0.5*m_height;			
			float alpha = atan2((float)y2, (float)x2);// ����ǥ�� ǥ��
			float r = sqrt((float)(x2*x2 + y2*y2));       
			float r2 = 0.5*m_width;                  // �ִ� ȸ�� ������
			if (r>r2)                                  //�ִ� ȸ�� �������� �ʰ��� ���
			{
				for (int k = 0; k < m_channals; k++)
					dst.at<Vec3b>(Point(x, y))[k] = biLinear(x, y, k);// ��ǥ �״�� ����
				continue;                                 
			}	
			a = r*cos(alpha + th*(r2-r)/(r2)) + r2;					// �ʰ����� ���� ��� ȸ�� ����
			b = r*sin(alpha + th*(r2-r)/(r2)) + r2;
			for (int k = 0; k < m_channals; k++)
			{
				if ((uchar)biLinear(a, b, k))
					dst.at<Vec3b>(y, x)[k] = (uchar)biLinear(a, b, k);
			}
		}
	}
	return 0;
}

int Image::BTrans(Mat &dst, vector<Point>mUp, vector<Point>mDown)	//B�� �ĵ�
{ 
	for (int a = 0; a < mUp.size(); a++)
	{
		int N,Dx,Dy,Kx,Ky;
		Dy = mDown[a].x - mUp[a].x;   Dx = mDown[a].y - mUp[a].y;   //���콺 Ŭ���� ���������� ��ǥ �Ÿ�
		N = 16;	Ky = mUp[a].y / N;     Kx = mUp[a].x / N;         
		                  				
		for (int i = 0; i < m_height; i++)	
		{ 
			for (int j = 0; j < m_width; j++) 
			{
				int l,m;	double x,y;
				l = Ky - i / N;           // 0<= l, m <=3
				m = Kx - j / N;
				x = i;		y = j;           								
				if ((l >= 0) && (l <= 3) && (m >= 0) && (m <= 3)) //������� �� ��� �̵��� ��ǥ�� �̵�
				{
					double u, v;
					u = (double)i / N - (int)(i / N);     
					v = (double)j / N - (int)(j / N);
					x += Dx * (BSpline(m, v)) * (BSpline(l, u));
					y += Dy * (BSpline(m, v)) * (BSpline(l, u));
				}
				for (int k = 0; k < m_channals; k++) // ��ǥ�� ȭ�� �ݿ� 
				{
					if ((uchar)biLinear(x, y, k))
						m_ori.at<Vec3b>(i, j)[k] = (uchar)biLinear(y, x, k);
				}
			}
		}
		dst = m_ori.clone();
	}
	return 0;
}
