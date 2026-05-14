/*PLEASE DO NOT EDIT THIS CODE*/
/*This code was generated using the UMPLE 1.32.1.6535.66c005ced modeling language!*/

package example;

// line 3 "../../test.ump"
public class Moving
{

  //------------------------
  // MEMBER VARIABLES
  //------------------------

  //Moving State Machines
  public enum Action { going, turning }
  private Action action;

  //------------------------
  // CONSTRUCTOR
  //------------------------

  public Moving()
  {
    setAction(Action.going);
  }

  //------------------------
  // INTERFACE
  //------------------------

  public String getActionFullName()
  {
    String answer = action.toString();
    return answer;
  }

  public Action getAction()
  {
    return action;
  }

  public boolean obstacle()
  {
    boolean wasEventProcessed = false;
    
    Action aAction = action;
    switch (aAction)
    {
      case going:
        // line 5 "../../test.ump"
        turn();
        setAction(Action.turning);
        wasEventProcessed = true;
        break;
      default:
        // Other states do respond to this event
    }

    return wasEventProcessed;
  }

  public boolean clear()
  {
    boolean wasEventProcessed = false;
    
    Action aAction = action;
    switch (aAction)
    {
      case turning:
        // line 6 "../../test.ump"
        go();
        setAction(Action.going);
        wasEventProcessed = true;
        break;
      default:
        // Other states do respond to this event
    }

    return wasEventProcessed;
  }

  private void setAction(Action aAction)
  {
    action = aAction;
  }

  public void delete()
  {}

}