// obsave.c

int is_ob_saved() { return 1; }

int save()
{
        if( this_object()->is_warcraft() )
                WARCRAFT_DBASE_D->set_data(this_object()->save_dbase_data());
        else if( this_object()->is_cruise_ob() )
                BAG_DBASE_D->set_data(this_object()->save_dbase_data());
        DBASE_D->set_data(this_object()->save_dbase_data());
        return 1;
}

int restore()
{
        if( this_object()->is_room() )
        else if( this_object()->is_cruise_ob() )
        else if( this_object()->is_item_make() )
        this_object()->receive_dbase_data(DBASE_D->query_data());

        return 1;
}
