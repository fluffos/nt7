// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;35m香飘飘[2;37;0m[2;37;0m", ({"yiyayo"}));        
        set("gender", "女性");                
        set("long", "大法[2;37;0m
它是道知天的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "akoi");
        set("owner_name", "道知天");
        set_temp("owner", "akoi");
        set_temp("owner_name", "道知天");
        ::setup();
}
