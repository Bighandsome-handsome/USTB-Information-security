#pragma once
//Ϊ�˺���ʹ��pow sqrt sin�Ⱥ�����ʱ���С��ӡ�double��ת������float�������ܶ�ʧ���ݡ��ľ���
//��ԭ����float��������ȫ����Ϊdouble
class Calculator                                  //����һ�������
{
public:
	virtual void Input() = 0;                    //�麯�������벢ȡ�������������
	virtual double calculate()=0;                 //�麯����ִ��ʵ�ʵļ��㣬�����ؽ��
	virtual void Menu(Calculator* pCal)=0;       //�麯����ѡ��˵����ܣ�ִ���������㣩
	 //pCal��ָ��ǰ����������Ķ����ָ��
};