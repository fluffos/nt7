// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;34m[35m峰火不扰关[2;37;0m[2;37;0m", ({"sleepbag"}));        
        set("gender", "女性");                
        set("long", "好大一条龙。[2;37;0m
它是空虚公子的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "kid");
        set("owner_name", "空虚公子");
        set_temp("owner", "kid");
        set_temp("owner_name", "空虚公子");
        ::setup();
}
