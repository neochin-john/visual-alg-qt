#include "visuallist.h"
#include "algscene.h"

#include <QThread>

VisualList::VisualList(const QList<int> &data)
{
    m_originList = data;
    for (int i = 0; i < m_originList.size(); i++)
    {
        m_data.append(VisualListElement{m_originList.at(i), i, this});
    }
}

void wait()
{
    QThread::sleep(1);
}

void VisualList::swap(int idx1, int idx2)
{
    int tmpVal = m_data[idx1].val();
    m_data[idx1].setVal(m_data[idx2].val());
    m_data[idx2].setVal(tmpVal);
    emit s_swap(idx1, idx2);
    wait();
}

int VisualList::size()
{
    return m_data.size();
}

VisualListElement &VisualList::operator [](int idx)
{
    return m_data[idx];
}

VisualListElement::VisualListElement(int val, int idx, VisualList *list)
{
    m_val = val;
    m_idxInList = idx;
    m_list = list;
}

int VisualListElement::val()
{
    return m_val;
}

void VisualListElement::setVal(int val)
{
    this->m_val = val;
}

bool VisualListElement::operator <(const VisualListElement &ele)
{
    bool ret = this->m_val < ele.m_val;
    emit m_list->s_compare(this->m_idxInList, ele.m_idxInList);
    wait();
    return ret;
}

bool VisualListElement::operator <=(const VisualListElement &ele)
{
    bool ret = this->m_val <= ele.m_val;
    emit m_list->s_compare(this->m_idxInList, ele.m_idxInList);
    wait();
    return ret;
}

bool VisualListElement::operator >(const VisualListElement &ele)
{
    bool ret = this->m_val > ele.m_val;
    emit m_list->s_compare(this->m_idxInList, ele.m_idxInList);
    wait();
    return ret;
}

bool VisualListElement::operator >=(const VisualListElement &ele)
{
    bool ret = this->m_val >= ele.m_val;
    emit m_list->s_compare(this->m_idxInList, ele.m_idxInList);
    wait();
    return ret;
}

bool VisualListElement::operator ==(const VisualListElement &ele)
{
    bool ret = this->m_val == ele.m_val;
    emit m_list->s_compare(this->m_idxInList, ele.m_idxInList);
    wait();
    return ret;
}

bool VisualListElement::operator !=(const VisualListElement &ele)
{
    bool ret = this->m_val != ele.m_val;
    emit m_list->s_compare(this->m_idxInList, ele.m_idxInList);
    wait();
    return ret;
}
