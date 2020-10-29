// mbook.c
// This program is a part of NITAN MudLIB 
// redl 2012/11/1 
#include <ansi.h>
#include <medical.h>

inherit MEDICAL_BOOK;

void create()
{
        set_name(HIY "炼丹笔记" NOR, ({ "liandan biji", "biji" }));
        set_weight(500);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("unit", "本");
                set("long", "这是一本誊写的小本，上面用小篆书写着“炼丹笔记”几个字。\n");
                set("material", "paper");
                set("dynamic_quest", 1);
                set("no_sell", "这样东西不能离开你。\n");
                set("no_put", "这样东西不能放在那儿。\n");
                set("no_store", "这样东西不能放在那儿。\n");
                set("no_get", "这样东西不能离开那儿。\n");
                set("no_steal", "这样东西不能离开那儿。\n");
                set("no_beg", "这样东西不能离开那儿。\n");
                set("base_value", 0);
                set("skill", ([
                        "name": "liandan-shu",
                        "jing_cost": 80,
                        "difficulty": 40,
                        "max_skill": 150,
                        "min_skill": 30,
                ]));

                set("can_make", ([
                        "shujing"  : 50,        // 舒筋活络丹
                        "dieda"    : 50,        // 跌打伤愈膏
                        "jiedu"    : 100,       // 牛黄解毒丸
                        "yuzhen"   : 250,       // 玉真散
                        "yuling"   : 250,       // 玉灵散
                        "yuqing"   : 300,       // 玉清散
                ]));
        }
        setup();
}
