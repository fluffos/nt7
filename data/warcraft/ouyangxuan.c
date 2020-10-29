// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("汉生麒麟[2;37;0m[2;37;0m", ({"ouyangxuanride"}));        
        set("gender", "男性");                
        set("long", "汉生麒麟[2;37;0m
它是欧阳汉生的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "ouyangxuan");
        set("owner_name", "欧阳汉生");
        set_temp("owner", "ouyangxuan");
        set_temp("owner_name", "欧阳汉生");
        ::setup();
}
