// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[5m[1;35m万[1;34m恶[1;31m之[1;32m源[2;37;0m[2;37;0m", ({"evilall"}));        
        set("gender", "女性");                
        set("long", "万恶之源！[2;37;0m
它是拳拳盛意的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "skyevil");
        set("owner_name", "拳拳盛意");
        set_temp("owner", "skyevil");
        set_temp("owner_name", "拳拳盛意");
        ::setup();
}
