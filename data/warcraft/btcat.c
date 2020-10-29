// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;36m青色的骆驼[2;37;0m[2;37;0m", ({"jinhu"}));        
        set("gender", "男性");                
        set("long", "$HIC$青色的骆驼[2;37;0m
它是欧阳丑的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "btcat");
        set("owner_name", "欧阳丑");
        set_temp("owner", "btcat");
        set_temp("owner_name", "欧阳丑");
        ::setup();
}
