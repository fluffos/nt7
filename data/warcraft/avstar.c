// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m玄武[2;37;0m[2;37;0m", ({"xuanwu"}));        
        set("gender", "女性");                
        set("long", "大乌龟[2;37;0m
它是黑衣的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "avstar");
        set("owner_name", "黑衣");
        set_temp("owner", "avstar");
        set_temp("owner_name", "黑衣");
        ::setup();
}
