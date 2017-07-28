//*********** (C) Copyright 2010 David Martin All rights reserved. **********
// Purpose: List Class Code 

//****************************************************************************************


#using "System.Xml.dll"

#using "System.Management.dll"

using namespace System;
using namespace System::IO;
using namespace System::Collections::Generic;
using namespace System::Windows;
using namespace System::Windows::Forms;



// ----------------------------------------------------------------
//  Name:           ListNode
//	Structure:		ListNode
//  Description:    single element in a linked list. 
//  Arguments:      NONE
//  Return Value:   NONE
// ----------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////////////////////////////////


generic <typename T>
public ref struct ListNode
{
   ListNode<T>(T t) : item(t) { }//constructor
        
   T item;//data
   
   ListNode<T>^ next; //next node
};


// ----------------------------------------------------------------
//  Name:           MyList
//	Class:			ListNode
//  Description:    represents a linked list. 
//  Arguments:      NONE
//  Return Value:   NONE
// ----------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////////////////////////////////

generic <typename T>
public ref class MyList : IEnumerable<ListNode<T>^>
{
   ListNode<T>^ first;//first node
   int listCounter;//count of amount of nodes in the list

   public:

      property bool changed;//flag to state whether or not the list is changed





// ----------------------------------------------------------------
//  Name:           getListCounter
//	Class:			MyList
//  Description:    return the list counter 
//  Arguments:      NONE
//  Return Value:   int
// ----------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////////////////////////////////
	int getListCounter()
	{
		return listCounter;
	}

// ----------------------------------------------------------------
//  Name:           Add
//	Class:			MyList
//  Description:    Add an item to the end of the list 
//  Arguments:      T
//  Return Value:   VOID
// ----------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////////////////////////////////
      
       bool Add(T t)
      {
		  try
		  {
			  changed = true;//set flag to true
			  if (first == nullptr)//if the first node is null
				{
					first = gcnew ListNode<T>(t);//create first node
					listCounter=0;//set the list counter to 0
					return true;
				}
				else//otherwise
				{
					ListNode<T>^ node = first;//create a node that is equal to the first
					while (node->next != nullptr)//while the next node is not NULL
					{
						node = node->next;//move forward through the list
					}
					node->next = gcnew ListNode<T>(t);//create new node in the list
					listCounter++;//increment counter
					return true;
				}
		  }
		  catch (Exception ^e)//catch unforeseen error and display error
		{
			MessageBox::Show(String::Format("Error: ", e->Message),"ERROR",Forms::MessageBoxButtons::OK);
			return false;
		}
	   }
// ----------------------------------------------------------------
//  Name:           Remove
//	Class:			MyList
//  Description:	remove an item from the list;Return true if the object was removed,
					// false if it was not found. 
//  Arguments:      T
//  Return Value:   BOOL
// ----------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
	  bool Remove( ListNode<T>^ p_iter )
    {
		try
		{
			changed = true;//set the changed flag to true
			if (first == nullptr)//if the first node is true
				return false;//return false
			if (first = p_iter)//if the first node equals the node provided
			{
				 first = first->next;//move the first node up the list
				listCounter--;//decrement the list
				return true;//return success
			}
		  //otherwise
          ListNode<T>^ node = first;//set the node to the first node
          while(node->next != nullptr)//while next node is NULL
		  {
             if (node->next == p_iter)//if the next node equal to the provided node
             {
                 node->next = node->next->next;//connect to the next node, skipping the found node
				 listCounter--;//decrement counter
                 return true;//return success
             }
             node = node->next;//forward to the next node in the list
          }
          return false;//return false
		}
		catch (Exception ^e)//catch unforeseen error and display error
		{
			MessageBox::Show(String::Format("Error: ", e->Message),"ERROR",Forms::MessageBoxButtons::OK);
			return false;
		}
	  }



// ----------------------------------------------------------------
//  Name:           Remove
//	Class:			MyList
//  Description:	remove all the items on the list 
//  Arguments:      T
//  Return Value:   BOOL
// ----------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool RemoveAll()
      {
		  try
		  {
			  changed = true;//set list flag to true
			  while(first != nullptr)//while iterator is not null
			  {
				first = first->next;//set the first node to the next node
				listCounter--;//decrement list
			  }

			  if(first == nullptr)//if the first node is null
				return true;//return success
			  else
				return false;//return failed
		  }
		  catch (Exception ^e)//catch unforeseen error and display error
		  {
			MessageBox::Show(String::Format("Error: ", e->Message),"ERROR",Forms::MessageBoxButtons::OK);
			return false;
		  }	
       }



// ----------------------------------------------------------------
//  Name:           First:Get
//	Class:			MyList
//  Description:	returns the first node 
//  Arguments:      NONE
//  Return Value:   ListNode<T>^
// ----------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////////////////////////////////
   property ListNode<T>^ First
      {
         ListNode<T>^ get()
          {
             return first;//return first node
          }
      }

   private:

// ----------------------------------------------------------------
//  Name:           GetEnumerator_NG
//	Class:			MyList
//  Description:	sealed non-generic inherited GetEnumerator
//  Arguments:      NONE
//  Return Value:   System::Collections::IEnumerator^
// ----------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////////////////////////////////
      virtual System::Collections::IEnumerator^ GetEnumerator_NG() sealed
                = System::Collections::IEnumerable::GetEnumerator
      {
         return GetEnumerator();//extract enumerator
      }

// ----------------------------------------------------------------
//  Name:           GetEnumerator_G
//	Class:			MyList
//  Description:	sealed generic inherited GetEnumerator
//  Arguments:      NONE
//  Return Value:   IEnumerator<ListNode<T>^>^
// ----------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////////////////////////////////
 
      virtual IEnumerator<ListNode<T>^>^ GetEnumerator_G() sealed
                = IEnumerable<ListNode<T>^>::GetEnumerator
      {
          return GetEnumerator();//extract enumerator
      }

   public:
// ----------------------------------------------------------------
//  Name:           GetEnumerator
//	Class:			MyList
//  Description:	creates enumerator and returns enumerator
//  Arguments:      NONE
//  Return Value:   IEnumerator<ListNode<T>^>^
// ----------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////////////////////////////////

      IEnumerator<ListNode<T>^>^ GetEnumerator()
      {
          ListEnumerator<T>^ enumerator = gcnew ListEnumerator<T>(this);
          return (IEnumerator<ListNode<T>^>^) enumerator; //extract enumerator
      }

// ----------------------------------------------------------------
//  Name:           ListEnumerator
//	Structure:		ListEnumerator
//  Description:	structure for the list ennumerator for "for each" function
//  Arguments:      NONE
//  Return Value:   IEnumerator<ListNode<T>^>^
// ----------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////////////////////////////////
      generic <typename T> ref struct ListEnumerator : IEnumerator<ListNode<T>^>
      {
          ListNode<T>^ current;//current node
          MyList<T>^ theList; //list
          bool beginning;//beginning flag

// ----------------------------------------------------------------
//  Name:           ListEnumerator
//	Structure:		ListEnumerator
//  Description:	constructor
//  Arguments:      NONE
//  Return Value:   IEnumerator<ListNode<T>^>^
// ----------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////////////////////////////////
  ListEnumerator<T>(MyList<T>^ list) : theList(list), beginning(true)
          {
              theList->changed = false;//set the changed flag to false, initialize the list, set the beginning flag to true
          }

          private:


// ----------------------------------------------------------------
//  Name:           ~ListEnumerator()
//	Structure:		ListEnumerator
//  Description:	Deconstructor
//  Arguments:      NONE
//  Return Value:   VOID
// ----------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////////////////////////////////
               ~ListEnumerator () {}//deconstructor

        

// ----------------------------------------------------------------
//  Name:           Current_NG:get
//	Structure:		ListEnumerator
//  Description:	return non-generic current node
//  Arguments:      NONE
//  Return Value:   Object^
// ----------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////////////////////////////////

            virtual property Object^ Current_NG
             {
                 Object^ get() sealed =
                    System::Collections::IEnumerator::Current::get
                 {
                    return (Object^) Current;
                 }
             }
// ----------------------------------------------------------------
//  Name:           Current_G:get
//	Structure:		ListEnumerator
//  Description:	return generic current node
//  Arguments:      NONE
//  Return Value:   ListNode<T>^
// ----------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////////////////////////////////
            virtual property ListNode<T>^ Current_G
             {
                 ListNode<T>^ get() sealed = IEnumerator<ListNode<T>^>::Current::get
                 {
                    return Current;
                 }
             }

          public:

// ----------------------------------------------------------------
//  Name:           Current:get
//	Structure:		ListEnumerator
//  Description:	return current node if the list has not changed
//  Arguments:      NONE
//  Return Value:   ListNode<T>^
// ----------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////////////////////////////////
              property ListNode<T>^ Current
             {
                 ListNode<T>^ get()
                 {
                     if (theList->changed)
                        throw gcnew InvalidOperationException();
                     return current;
                 }
             }
// ----------------------------------------------------------------
//  Name:           MoveNext
//	Structure:		ListEnumerator
//  Description:	if the list has not changed
//					and if the current node is not null, then go to the next node
//					or if the current node is null, then return the first node
//					if the resulting node is not null, return true
//					otherwise return false
//  Arguments:      NONE
//  Return Value:   ListNode<T>^
// ----------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////////////////////////////////
               virtual bool MoveNext()
             {
				 try
				 {
					 if (theList->changed)//if the list has not changed
						throw gcnew InvalidOperationException();//throw error
					beginning = false;//set the beginning to false
					if (current != nullptr)//if the current node is not null
					{
						current = current->next;//move the current node forward
					}
					else
						current = theList->First;//otherwise set it to first

					if (current != nullptr)//if the current node is not null
						return true;//return success
					else
						return false;//return failed
				}
				 catch (Exception ^e)//catch unforeseen error and display error
				 {
					MessageBox::Show(String::Format("Error: ", e->Message),"ERROR",Forms::MessageBoxButtons::OK);
					return false;
				  }
			   }

// ----------------------------------------------------------------
//  Name:           Reset
//	Structure:		ListEnumerator
//  Description:	set changed flag to false and set the current node to the head
//  Arguments:      NONE
//  Return Value:   VOID
// ----------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////////////////////////////////
             virtual void Reset()
              {
				  try
				  {

					theList->changed = false;//set the list changed flag to false
					current = theList->First;//set the current node to the first node
	              }
				  catch (Exception ^e)//catch unforeseen error and display error
				  {
					  MessageBox::Show(String::Format("Error: ", e->Message),"ERROR",System::Windows::Forms::MessageBoxButtons::OK);
				  }
			 }
}; // end of ListEnumerator

}; // end of MyList
