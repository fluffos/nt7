// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;36m圆圆[2;37;0m[2;37;0m", ({"chenyys"}));        
        set("gender", "男性");                
        set("long", "呵呵[2;37;0m
它是陈圆圆的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "chenyy");
        set("owner_name", "陈圆圆");
        set_temp("owner", "chenyy");
        set_temp("owner_name", "陈圆圆");
        ::setup();
}
