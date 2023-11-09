#ifndef VISUALLIST_H
#define VISUALLIST_H

#include <QList>

class VisualList;
class VisualListElement
{
public:
    VisualListElement(int val, int idx, VisualList *list);
    int val();
    void setVal(int val);

    bool operator < (const VisualListElement &ele);
    bool operator <= (const VisualListElement &ele);
    bool operator > (const VisualListElement &ele);
    bool operator >= (const VisualListElement &ele);
    bool operator == (const VisualListElement &ele);
    bool operator != (const VisualListElement &ele);

private:
    int m_val;
    int m_idxInList;
    VisualList *m_list;
};

class VisualList : public QObject
{
    Q_OBJECT

public:
    VisualList(const QList<int> &data);
    void swap(int idx1, int idx2);
    int size();
    VisualListElement& operator [](int idx);

signals:
    void s_compare(int idx1, int idx2);
    void s_swap(int idx1, int idx2);

private:
    QList<int> m_originList;
    QList<VisualListElement> m_data;
};

#endif // VISUALLIST_H
