// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m浴血凤凰[2;37;0m[2;37;0m", ({"mypet"}));        
        set("gender", "男性");                
        set("long", "浴血凤凰[2;37;0m
它是氧化钙的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "cao");
        set("owner_name", "氧化钙");
        set_temp("owner", "cao");
        set_temp("owner_name", "氧化钙");
        ::setup();
}
