// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;36m路灯[2;37;0m[2;37;0m", ({"aiyuhs"}));        
        set("gender", "男性");                
        set("long", "我是照明的路灯，属国家财产其他人等不得损坏。[2;37;0m
它是爱雨的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "aiyu");
        set("owner_name", "爱雨");
        set_temp("owner", "aiyu");
        set_temp("owner_name", "爱雨");
        ::setup();
}
