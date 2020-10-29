// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m大唧唧[2;37;0m[2;37;0m", ({"djj"}));        
        set("gender", "男性");                
        set("long", "大唧唧[2;37;0m
它是贾公公的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "ihavejj");
        set("owner_name", "贾公公");
        set_temp("owner", "ihavejj");
        set_temp("owner_name", "贾公公");
        ::setup();
}
