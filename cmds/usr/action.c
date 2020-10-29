inherit F_CLEAN_UP; 

int main(object me, string arg) 
{
        write("/adm/daemons/actiond"->query_action_string());
        return 1;
}
