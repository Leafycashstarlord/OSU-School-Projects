<?php
	session_start();	
// Include config file
	require_once "config.php";
 
// Define variables and initialize with empty values
// Note: You can not update SSN 
$Dname = $Bdate = $Relationship = $Sex = "";
$Dname_err = $Birth_err = $Relationship_err = $Sex_err = "" ;
// Form default values

if(isset($_GET["Dname"]) && !empty(trim($_GET["Dname"]))){
	$_SESSION["Dname"] = $_GET["Dname"];

    // Prepare a select statement
    $sql1 = "SELECT * FROM DEPENDENT WHERE Essn = ? AND Dependent_name = ?";
  
    if($stmt1 = mysqli_prepare($link, $sql1)){
        // Bind variables to the prepared statement as parameters
        mysqli_stmt_bind_param($stmt1, "is", $param_Essn, $param_Dname);      
        // Set parameters
       $param_Essn = $_SESSION["Ssn"];
       $param_Dname = $_SESSION["Dname"];

        // Attempt to execute the prepared statement
        if(mysqli_stmt_execute($stmt1)){
            $result1 = mysqli_stmt_get_result($stmt1);
			if(mysqli_num_rows($result1) > 0){

				$row = mysqli_fetch_array($result1);

				$Dname = $row['Dependent_name'];
				$Essn = $row['Essn'];
				$Bdate = $row['Bdate'];
				$Relationship = $row['Relationship'];
				$Sex = $row['Sex'];
			}
		}
	}
}

 
// Post information about the employee when the form is submitted
// Processing form data when form is submitted
if($_SERVER["REQUEST_METHOD"] == "POST"){
    // the id is hidden and can not be changed
    $Essn = $_SESSION["Ssn"];
    $Oname = $_SESSION["Dname"];
    // Validate form data this is similar to the create Employee file
    // Validate name
    $Dname = trim($_POST["Dname"]);
    if(empty($Dname)){
        $Dname_err = "Please enter a Dname.";
    } elseif(!filter_var($Dname, FILTER_VALIDATE_REGEXP, array("options"=>array("regexp"=>"/^[a-zA-Z\s]+$/")))){
        $Dname_err = "Please enter a valid dependent.";
    } 
    $Relationship = trim($_POST["Relationship"]);
    if(empty($Relationship)){
        $Relationship_err = "Please enter a relationship.";
    } elseif(!filter_var($Relationship, FILTER_VALIDATE_REGEXP, array("options"=>array("regexp"=>"/^[a-zA-Z\s]+$/")))){
        $Relationship_err = "Please enter a valid relationship.";
    }
    // Validate Sex
    $Sex = trim($_POST["Sex"]);
    if(empty($Sex)){
        $Sex_err = "Please enter Sex.";     
    }
    // Validate Birthdate
    $Bdate = trim($_POST["Bdate"]);
    if(empty($Bdate)){
        $SBdate_err = "Please enter birthdate.";     
    }

    // Check input errors before inserting into database
    if(empty($Dname_err) && empty($Relationship_err) && empty($Sex_err) && empty($Birth_err)){
        // Prepare an update statement
        $sql = "UPDATE DEPENDENT SET Dependent_name=?, Sex=?, Bdate=?, Relationship = ? WHERE Essn=? AND Dependent_name = ?";
    
        if($stmt = mysqli_prepare($link, $sql)){
            // Bind variables to the prepared statement as parameters
            mysqli_stmt_bind_param($stmt, "isssss", $param_Essn, $param_Dname, $param_Relationship, $param_Sex, $param_Bdate, $param_Oname);
            
            // Set parameters
            $param_Essn = $Essn;
            $param_Dname = $Dname;
			$param_Relationship = $Relationship;            
			$param_Sex = $Sex;
            $param_Bdate = $Bdate;
            $param_Oname = $Oname;
            
            // Attempt to execute the prepared statement
            if(mysqli_stmt_execute($stmt)){
                // Records updated successfully. Redirect to landing page
                header("location: index.php");
                exit();
            } else{
                echo "<center><h2>Error when updating</center></h2>";
            }
        }        
        // Close statement
        mysqli_stmt_close($stmt);
    }
    
    // Close connection
    mysqli_close($link);
}
?>
 
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Company DB</title>
    <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.css">
    <style type="text/css">
        .wrapper{
            width: 500px;
            margin: 0 auto;
        }
    </style>
</head>
<body>
    <div class="wrapper">
        <div class="container-fluid">
            <div class="row">
                <div class="col-md-12">
                    <div class="page-header">
                        <h3>Update Record for SSN =  <?php echo $_SESSION["Ssn"]; ?> </H3>
                    </div>
                    <p>Please edit the input values and submit to update.
                    <form action="<?php echo htmlspecialchars(basename($_SERVER['REQUEST_URI'])); ?>" method="post">
						<div class="form-group <?php echo (!empty($Dname_err)) ? 'has-error' : ''; ?>">
                            <label>Dependent Name</label>
                            <input type="text" name="Dname" class="form-control" value="<?php echo $Dname; ?>">
                            <span class="help-block"><?php echo $Dname_err;?></span>
                        </div>
						<div class="form-group <?php echo (!empty($Relationship_err)) ? 'has-error' : ''; ?>">
                            <label>Relationship</label>
                            <input type="text" name="Relationship" class="form-control" value="<?php echo $Relationship; ?>">
                            <span class="help-block"><?php echo $Relationship_err;?></span>
                        </div>
						<div class="form-group <?php echo (!empty($Sex_err)) ? 'has-error' : ''; ?>">
                            <label>Sex</label>
                            <input type="text" name="Sex" class="form-control" value="<?php echo $Sex; ?>">
                            <span class="help-block"><?php echo $Sex_err;?></span>
                        </div>
                        <div class="form-group <?php echo (!empty($Birth_err)) ? 'has-error' : ''; ?>">
                            <label>Birth Date</label>
                            <input type="date" name="Bdate" class="form-control" value="<?php echo $Bdate; ?>">
                            <span class="help-block"><?php echo $Birth_err;?></span>
                        </div>						
                        <input type="hidden" name="Ssn" value="<?php echo $Essn; ?>"/>
                        <input type="submit" class="btn btn-primary" value="Submit">
                        <a href="index.php" class="btn btn-default">Cancel</a>
                    </form>
                </div>
            </div>        
        </div>
    </div>
</body>
</html>