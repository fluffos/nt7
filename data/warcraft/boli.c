// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("功夫熊猫[2;37;0m[2;37;0m", ({"kiss"}));        
        set("gender", "男性");                
        set("long", "它来自动物园...[2;37;0m
它是功夫小子的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "boli");
        set("owner_name", "功夫小子");
        set_temp("owner", "boli");
        set_temp("owner_name", "功夫小子");
        ::setup();
}
