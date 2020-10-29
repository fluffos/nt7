// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m五[1;35m花[1;36m马[2;37;0m[2;37;0m", ({"baima"}));        
        set("gender", "女性");                
        set("long", "$HIW$五$HIM$花$HIC$马[2;37;0m
它是欧阳询的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "peno");
        set("owner_name", "欧阳询");
        set_temp("owner", "peno");
        set_temp("owner_name", "欧阳询");
        ::setup();
}
