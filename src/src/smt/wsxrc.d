#----------------------------------------------------------------------------
#   Dialog data and code block - do not modify this code by hand
#   Generated by LIBERO 2.30 on 14 Aug, 1998, 22:51.
#   Schema file used: lrschema.pl
#----------------------------------------------------------------------------

#-- Symbolic constants and event numbers ------------------------------------

$LR_defaults_state = 2;
$LR_STATE_after_init = 0;
$LR_STATE_have_input = 1;
$LR_STATE_defaults = 2;

$terminate_event = -1;                  # Halts the dialog
$LR_NULL_EVENT = -2;
$error_event = 0;
$exception_event = 1;
$finished_event = 2;
$ok_event = 3;

#-- Standard subroutines used by dialog interpreter -------------------------

sub raise_exception {
    local ($event) = @_;
    $the_exception_event = $event;
    $exception_raised = 1;
}

sub LR_initialise {
    $LR_nextst = "";
    $LR_nextst .= "0001";
    $LR_nextst .= "0011";
    $LR_nextst .= "0200";

    $LR_action = "";
    $LR_action .= "2001";
    $LR_action .= "0043";
    $LR_action .= "0200";

    $LR_module = "";
    $LR_module .= "060810090305" . "00";
    $LR_module .= "11" . "00";
    $LR_module .= "070405" . "00";
    $LR_module .= "020111" . "00";

    $LR_offset [1] = 0;
    $LR_offset [2] = 7;
    $LR_offset [3] = 9;
    $LR_offset [4] = 13;
}

#-- Dialog interpreter starts here ------------------------------------------

$feedback = 0;                          #   Main program feedback
$LR_state = 0;                          #   First state is always 0
&LR_initialise;                         #   Initialise static strings
&initialise_the_program;
while ($the_next_event != $terminate_event)
  {
    $LR_event = $the_next_event;
    $LR_event < 0 || $LR_event >= 4 && die
        "State ", $LR_state,
        " - event ", $LR_event, " is out of range\n";
    $LR_index = ($LR_state * 4 + $LR_event) * 1;
    $LR_index = substr ($LR_action, $LR_index, 1);
    $LR_savest = $LR_state;

    #   If no action for this event, try the defaults state
    if ($LR_index == 0)
      {
        $LR_state = $LR_defaults_state;
        $LR_index = ($LR_state * 4 + $LR_event) * 1;
        $LR_index = substr ($LR_action, $LR_index, 1);
        $LR_index == 0 && die
            "State ", $LR_state,
            " - event ", $LR_event, " is not accepted\n";
      }
    $the_next_event = $LR_NULL_EVENT;
    $the_exception_event = $LR_NULL_EVENT;
    $exception_raised = 0;

    #   Execute module list for state transition, 0 indicates end of list
    $LR_vecptr = $LR_offset [$LR_index];
    $LR_modnbr = substr ($LR_module, $LR_vecptr * 2, 2);
    while ($LR_modnbr > 0 && !$exception_raised)
      {
          {                             #   Execute the module
            $LR_modnbr == 1 && do { &close_output_file; last; };
            $LR_modnbr == 2 && do { &generate_output_footer; last; };
            $LR_modnbr == 3 && do { &generate_output_header; last; };
            $LR_modnbr == 4 && do { &generate_resource_item; last; };
            $LR_modnbr == 5 && do { &get_next_input_file; last; };
            $LR_modnbr == 6 && do { &initialise_program_data; last; };
            $LR_modnbr == 7 && do { &load_input_file_data; last; };
            $LR_modnbr == 8 && do { &load_xitami_mime_types; last; };
            $LR_modnbr == 9 && do { &open_output_file; last; };
            $LR_modnbr == 10 && do { &parse_argument_values; last; };
            $LR_modnbr == 11 && do { &terminate_the_program; last; };
          }
        $LR_vecptr++;
        $LR_modnbr = substr ($LR_module, $LR_vecptr * 2, 2);
      }

    #   Handle exception if any was raised
    if ($exception_raised)
      {
        $the_exception_event == $LR_NULL_EVENT ||
            ($LR_event = $the_exception_event);

        $the_next_event = $LR_event;
      }
    else
      {
        $LR_index = ($LR_state * 4 + $LR_event) * 1;
        $LR_state = substr ($LR_nextst, $LR_index, 1);
      }
    $LR_state = $LR_savest if ($LR_state == $LR_defaults_state);
    if ($the_next_event == $LR_NULL_EVENT)
      {
        &get_external_event;
        $the_next_event == $LR_NULL_EVENT && die
            "No event set after event ", $LR_event,
            " in state ", $LR_state, "\n";
      }
  }
exit ($feedback);
