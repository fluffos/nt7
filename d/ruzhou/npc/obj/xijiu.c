// Obj:/d/ruzhou/npc/obj/xijiu.c  喜酒
// llm 99/07

inherit ITEM;
inherit F_LIQUID;

void create()
{
        set_name("喜酒", ({"xi jiu", "jiu"}));
        set_weight(700);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("long", "一瓶做得十分精致的装上等好酒的喜酒瓶。\n");
                set("unit", "瓶");
                set("max_liquid", 15);
        }
        // because a container can contain different liquid
        // we set it to contain wine at the beginning
        set("liquid", ([
                "type": "alcohol",
                "name": "玉香醇",
                "remaining": 15,
                "drunk_apply": 3,
        ]));
}