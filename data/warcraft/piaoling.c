// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("无痕[2;37;0m[2;37;0m", ({"wuhen"}));        
        set("gender", "女性");                
        set("long", "无痕[2;37;0m
它是东方飘玲的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "piaoling");
        set("owner_name", "东方飘玲");
        set_temp("owner", "piaoling");
        set_temp("owner_name", "东方飘玲");
        ::setup();
}
