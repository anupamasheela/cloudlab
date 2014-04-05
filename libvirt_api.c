#include <stdio.h>
#include <stdlib.h>
#include <libvirt/libvirt.h>
void main()
{
    int i,val=-1,choice,num_domains;
    int *active_domains;
    char name[50];
    virConnectPtr conn;
    virDomainPtr vdp;
    conn = virConnectOpen("xen:///");
    if (conn == NULL) {
        fprintf(stderr, "Error opening connection to XEN:///  \n");
        return 1;
    }
    else
    {
	//For finding Active Devices
        num_domains=virConnectNumOfDomains(conn);
        active_domains=malloc(sizeof(int) * num_domains);
        num_domains = virConnectListDomains(conn, active_domains, num_domains);
        printf("\nActive domain IDs:");
        for (i = 0 ; i < num_domains ; i++) 
            printf("%d\t", active_domains[i]);
        free(active_domains);
        while(1)
        {
            printf("\n1.Start\n2.Suspend\n3.Resume\n4.Stop\n5.Exit\n");
            printf("\nEnter your choice:");
            scanf("%d",&choice);
            switch(choice)
            {
                case 1: printf("\n Enter the active domian name: ");
                        scanf("%s",name);
                        vdp=virDomainLookupByName(conn,name);
                        val=virDomainCreate(vdp);
                        if(val==0)      
                            printf("Started successfully...");
                        else
                            printf("Failed...");   
                        break;
                case 2: printf("\n Enter the active domian name: ");
                        scanf("%s",name);
                        vdp=virDomainLookupByName(conn,name);
                        val=virDomainSuspend(vdp);
                        if(val==0)
                            printf("Suspend successful...");
                        else
                            printf("Failed...");   
                        break;
                case 3: printf("\n Enter the active domian name: ");
                        scanf("%s",name);
                        vdp=virDomainLookupByName(conn,name);
                        val=virDomainResume(vdp);
                        if(val==0)                     
                            printf("Resume successful...");
                        else
                            printf("Failed...");   
                        break;
                case 4: printf("\n Enter the active domian name: ");
                        scanf("%s",name);
                        vdp=virDomainLookupByName(conn,name);
                        val=virDomainShutdown(vdp);
                        if(val==0)                     
                            printf("Shutdown successful...");
                        else
                            printf("Failed...");   
                        break;
                case 5: exit(0);
                        break;
                default: printf("\nInvalid choice!");
                         break;
            }
        }
        virConnectClose(conn);
    }
}
