// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m小白[2;37;0m[2;37;0m", ({"xiaobai"}));        
        set("gender", "男性");                
        set("long", "我的乖乖小白[2;37;0m
它是墨子龙的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "xiaoqsc");
        set("owner_name", "墨子龙");
        set_temp("owner", "xiaoqsc");
        set_temp("owner_name", "墨子龙");
        ::setup();
}
