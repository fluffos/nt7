// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[5m[1;37m玉麒麟[2;37;0m[2;37;0m", ({"qilin"}));        
        set("gender", "女性");                
        set("long", "这是一只九天十地菩萨摇头怕怕霹雳精光玉麒麟。[2;37;0m
它是武当三米的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "debugc");
        set("owner_name", "武当三米");
        set_temp("owner", "debugc");
        set_temp("owner_name", "武当三米");
        ::setup();
}
