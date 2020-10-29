// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("呆[2;37;0m[2;37;0m", ({"baidu"}));        
        set("gender", "男性");                
        set("long", "呆呆呆呆呆呆呆呆呆呆呆呆呆呆呆呆呆呆呆呆呆呆呆呆呆呆呆[2;37;0m
它是懒羊羊的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "iiizy");
        set("owner_name", "懒羊羊");
        set_temp("owner", "iiizy");
        set_temp("owner_name", "懒羊羊");
        ::setup();
}
