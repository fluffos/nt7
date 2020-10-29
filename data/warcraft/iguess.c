// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;35m猜[1;36m猜[1;33m猜[2;37;0m[2;37;0m[2;37;0m", ({"guess"}));        
        set("gender", "男性");                
        set("long", "猜.....[2;37;0m
它是韩如钰的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "iguess");
        set("owner_name", "韩如钰");
        set_temp("owner", "iguess");
        set_temp("owner_name", "韩如钰");
        ::setup();
}
