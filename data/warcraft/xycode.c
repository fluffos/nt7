// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m无色牛[2;37;0m[2;37;0m", ({"niu"}));        
        set("gender", "男性");                
        set("long", "无色牛[2;37;0m
它是黄飞虎的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "xycode");
        set("owner_name", "黄飞虎");
        set_temp("owner", "xycode");
        set_temp("owner_name", "黄飞虎");
        ::setup();
}
