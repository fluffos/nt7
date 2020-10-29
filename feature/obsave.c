// obsave.c

int is_ob_saved() { return 1; }

int save()
{
        if( this_object()->is_cruise_ob() )
        {
                BBASE_D->set_data(this_object()->save_dbase_data()); 
                return 1;
        }

        DBASE_D->set_data(this_object()->save_dbase_data());
        return 1;
}

int restore()
{
        if( this_object()->is_cruise_ob() )
        {
                this_object()->receive_dbase_data(BBASE_D->query_data());
                return 1;
        }

        this_object()->receive_dbase_data(DBASE_D->query_data());
        return 1;
}
