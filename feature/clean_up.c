// clean_up.c
// by Annihilator@ES2

int clean_up()
{
        object *inv;
        int i;

        if( !clonep() && query("no_clean_up", this_object()) ) return 1;
        if( interactive(this_object()) ) return 1;
        // If we are contained in something, let environment do the clean
        // up instead of making recursive call. This will prevent clean-up
        // time lag.
        if( environment() ) return 1;

        inv = all_inventory();
        for( i=sizeof(inv)-1; i>=0; i-- )
                if( interactive(inv[i]) ||
                        query_temp("quest_ob", inv[i]) ||
                        inv[i]->is_stay_in_room() ) return 1;

        destruct(this_object());
        return 0;
}
