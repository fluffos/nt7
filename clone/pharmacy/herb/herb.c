// Herb.c
// For pharmacy use
// BY Landis@MYTH(2002.05.13)

#include <ansi.h>
#include <dbase.h>

inherit ITEM;

int tp, op, xp;
string *eng;
string s_name, unit, desc;

string* _tp = ({ "苦", "咸", "酸", "辛", "甘" });
string* _op = ({ "寒", "凉", "平", "温", "热" });
string* _xp = ({ "无", "有" });

void create()
{
        set_name("药材物件", ({ "herb", "object" }));

        setup();
}

int initialize(int id, string name, int *prop)
{
        mapping rt;

        tp = prop[0];
        op = prop[1];
        xp = prop[2];

        s_name = name;
        eng  = ({ "herb" });
        unit = "份";
        desc = 0;

        rt = PHARMACY_D->query_relation(id);
        if (mapp(rt))
        {
                eng  = rt["eng"];
                unit = rt["unit"];
                desc = rt["desc"];
        }

        set_name(name, ({ eng }));
        set("unit", unit);
        set("desc", desc);
        return 1;
}

int *prop() { return ({ tp, op ,xp }); }

string long()
{
        string long;

        long = WHT + s_name + "：\n";

        if (stringp(desc))
                long += desc + "\n";

        long += "味性：" + _tp[tp] + " 药性：" + _op[op];
        long += " 毒性：" + _xp[xp] + "\n" + NOR;

        return long;
}
