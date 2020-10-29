// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[30m我让你靠[2;37;0m[2;37;0m", ({"kaos"}));        
        set("gender", "男性");                
        set("long", "哈哈[2;37;0m
它是靠告非的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "kao");
        set("owner_name", "靠告非");
        set_temp("owner", "kao");
        set_temp("owner_name", "靠告非");
        ::setup();
}
