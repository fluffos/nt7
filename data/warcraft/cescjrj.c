// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m小[1;33m救星[1;36m[2;37;0m[2;37;0m", ({"zzlsh"}));        
        set("gender", "女性");                
        set("long", "ZZLSH[2;37;0m
它是叶倩的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "cescjrj");
        set("owner_name", "叶倩");
        set_temp("owner", "cescjrj");
        set_temp("owner_name", "叶倩");
        ::setup();
}
