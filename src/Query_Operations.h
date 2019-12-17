#include <math.h>

cell* UNION(cell* c1, cell* c2, cell* unionlist)
{
    if(c1 == NULL)
        return c2;
    else
        if(c2 == NULL)
            return c1;

    if(c1->cellid < c2->cellid)
    {
        cell* temp = new cell;
        temp->cellid = c1->cellid;
        unionlist = temp;
        unionlist->next = UNION(c1->next, c2, unionlist->next);
    }
    else
    {
        if(c1->cellid > c2->cellid)
        {
            cell* temp = new cell;
            temp->cellid = c2->cellid;
            unionlist = temp;
            unionlist->next = UNION(c1, c2->next, unionlist->next);
        }
        else
        {
            cell* temp = new cell;
            temp->cellid = c2->cellid;
            unionlist = temp;
            unionlist->next = UNION(c1->next, c2->next, unionlist->next);
        }
    }
    return unionlist;
}

cell* INTERSECTION(cell* c1, cell* c2, int skip_value, cell* intersection)
{
    if(c1 == NULL || c2 == NULL)
        return NULL;
    bool flag = 1;
    cell* temp;
    if(c1->cellid == c2->cellid)
    {
        temp = new cell;
        temp->cellid = c1->cellid;
        intersection = temp;
    }
    else
        flag = 0;
    if(c1->next == NULL || c2->next == NULL)
    {
        if (flag == 1)
            return intersection;
        else
            return NULL;
    }
    if (c1->next->cellid > c2->next->cellid )
    {
        if(fabs(c1->next->cellid - c2->cellid + 1) >= skip_value)
        {
            if (c2->skip != NULL)
                c2 = c2->skip;
            else
                c2 = c2->next;
        }
        else
            c2 = c2->next;
    }
    else
    {
        if (c1->next->cellid < c2->next->cellid)
        {
            if(fabs(c2->next->cellid - c1->cellid + 1) >= skip_value)
            {
                if (c1->skip != NULL)
                    c1 = c1->skip;
                else
                    c1 = c1->next;
            }
            else
                c1 = c1->next;
        }
        else
        {
            c1 = c1->next;
            c2 = c2->next;
        }
    }
    if (flag)
        intersection->next =  INTERSECTION(c1, c2, skip_value, intersection->next);
    else
        intersection =  INTERSECTION(c1, c2, skip_value, intersection);
    return intersection;
}