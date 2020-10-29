// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m红[1;32m绿[1;37m毛毛怪[2;37;0m[2;37;0m", ({"peach"}));        
        set("gender", "女性");                
        set("long", "一只长了一身红毛，头顶一撮绿毛的怪麒麟。[2;37;0m
它是薄东来的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "ipx");
        set("owner_name", "薄东来");
        set_temp("owner", "ipx");
        set_temp("owner_name", "薄东来");
        ::setup();
}
