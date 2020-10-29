// muxiang.c 大木箱

inherit ITEM;

int is_muxiang() { return 1; }

void create()
{
        set_name("大木箱", ({ "da muxiang", "muxiang"}));
        set_weight(20000);
        set_max_encumbrance(2000000000);
        // set_max_carryitems(200);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("unit", "个");
                set("long", "一个打造的结结实实的大木箱，上面还有贴着一张标签。\n这个木箱最多可以存放200个物品。\n你可以使用 idlabel 指令修改木箱的ID。\n你可以使用 namelabel 指令修改木箱的名字。\n不要给木箱起乱七八糟的名字，否则你会受到各种可能的惩罚！\n");
                set("value", 10000);
        }
}

int is_container() { return 1; }