// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;33m快乐鸟[2;37;0m[2;37;0m", ({"flyu"}));        
        set("gender", "男性");                
        set("long", "我是一只小~小~小鸟，一直想飞飞飞得更高[2;37;0m
它是冰寒风的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "lxddongone");
        set("owner_name", "冰寒风");
        set_temp("owner", "lxddongone");
        set_temp("owner_name", "冰寒风");
        ::setup();
}
