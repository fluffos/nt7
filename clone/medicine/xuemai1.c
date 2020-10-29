// xuemai1.c 血脉丹

#include <ansi.h>
#include "medicine.h"

int is_xuemai_dan() { return 1;}
void create()
{
        set_name(HIR "一品血脉丹" NOR, ({"xuemai dan1", "dan"}));
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("long", "这是一粒血脉丹，可激活体内血脉能力。\n");
                set("base_unit", "颗");

                set("base_value", 200000);
                set("base_weight", 80);
                set("only_do_effect", 1);
                set("mixture", ([
                        "herb" : ([ "drug1"   : 1,
                                    "blood"   : 1,
                                    "xuelian2": 1,
                                    "yulu"    : 1,
                                    "sheli4"  : 1,
                                    "renshen2": 1,
                                    "puti4"   : 1,
                                    "lingzhi2": 1,
                                    "dimai"   : 1 ]),
                        "neili" : 300,
                        "jing"  : 50,
                        "time"  : 5,
                        "min_level" : 600,
                        "medical" : 1000,
                        "liandan-shu" : 2700,
                ]));
        }
        set("level", 1);
        setup();
}

int do_effect(object me) 
{
        write("血脉丹只能在修炼血脉upblood时候服用。\n"); 
        return 1;
}
