// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[5m[1;33m筋[1;36m斗[1;37m云[2;37;0m[2;37;0m", ({"yun"}));        
        set("gender", "女性");                
        set("long", "秦云的法器，可以覆雨翻云[2;37;0m
它是秦云的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "qin");
        set("owner_name", "秦云");
        set_temp("owner", "qin");
        set_temp("owner_name", "秦云");
        ::setup();
}
