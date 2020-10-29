// This program is a part of NITAN MudLIB

#include <ansi.h>
inherit ITEM;

int is_magic_item() { return 1; }

void create()
{
        set_name(BLU "阎王契" NOR, ({ "contract" }) );
        set_weight(100);
        /*if( clonep() )
                set_default_object(__FILE__);
        else*/ {
                set("unit", "份");
                set("value", 10000);
                set("long", BLU "这是一份阎王契。\n" NOR);

        }
        setup();
}

string long()
{
        int i, n;
        string msg;
        string *rec;
        
        msg = query("long");         
        rec = query("offer");
        
        if( !rec ) return msg; 
        else {
                n = sizeof(rec);
                for( i=0; i<n; i++ ) {                        
                        msg += rec[i];
                }
                return msg;
        }
}