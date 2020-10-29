// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("日月镜[2;37;0m[2;37;0m", ({"riyuejing"}));        
        set("gender", "男性");                
        set("long", "日月镜[2;37;0m
它是凸透镜的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "riyue");
        set("owner_name", "凸透镜");
        set_temp("owner", "riyue");
        set_temp("owner_name", "凸透镜");
        ::setup();
}
