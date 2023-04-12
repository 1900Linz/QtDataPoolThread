#pragma once

#include <QThread>
#include <QMutex>
#include <QWaitCondition>
#include <QQueue>

/*
Note:
    1.�������ݴ��䣬���߳̽��պʹ���
    2.���ݿ���߳�д��
*/
class QDataPoolBasic :
    public QThread
{
    Q_OBJECT
public:
    QDataPoolBasic(unsigned type, QObject* parent = 0);

    ~QDataPoolBasic();

    bool recvData(QByteArray data);

    bool recvData(char* data, unsigned len);

    void setPoolSize(unsigned size);

    void turn_on();

    void turn_off();

protected:
    void run() override;

    virtual void handleData(QByteArray,unsigned) = 0; /*������Ҫ����ʵ�ִ�����*/

private:
    QMutex m_threadRunnableMutex; /*�߳���*/

    QWaitCondition m_waitCondition; /*���ݶ��п�ʱ������ͣ�ȴ�״̬�������ݽ���ʱ�����߳�*/

    unsigned m_poolSize;            /*��������*/

    QQueue<QByteArray> m_dataQueue; /*���ݶ���*/

    volatile bool m_stopped;

    unsigned m_type; 
};

