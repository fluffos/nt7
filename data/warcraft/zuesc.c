// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[30m墨玉[2;37;0m[2;37;0m[2;37;0m", ({"moyuc"}));        
        set("gender", "女性");                
        set("long", "呵呵[2;37;0m
它是叶绿三风的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "zuesc");
        set("owner_name", "叶绿三风");
        set_temp("owner", "zuesc");
        set_temp("owner_name", "叶绿三风");
        ::setup();
}
