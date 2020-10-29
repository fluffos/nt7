// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m小白[2;37;0m[2;37;0m[2;37;0m", ({"xiaobai"}));        
        set("gender", "女性");                
        set("long", "我的乖乖小白[2;37;0m
它是墨子芸的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "xiaoqsb");
        set("owner_name", "墨子芸");
        set_temp("owner", "xiaoqsb");
        set_temp("owner_name", "墨子芸");
        ::setup();
}
