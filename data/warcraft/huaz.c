// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;34m凌志[2;37;0m[2;37;0m", ({"lexus"}));        
        set("gender", "男性");                
        set("long", "凌志是日本豐田汽車旗下銷售的獨立高級轎車品牌。[2;37;0m
它是花花太帅的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "huaz");
        set("owner_name", "花花太帅");
        set_temp("owner", "huaz");
        set_temp("owner_name", "花花太帅");
        ::setup();
}
